/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:08:31 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/21 17:15:13 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	increment_frame(t_ent *e)
{
	e->cur_frame_index++;
	if (e->cur_frame_index > e->frames_amount - 1 || \
		!e->anim_frames[e->cur_frame_index])
		e->cur_frame_index = 0;
	e->cur_frame = e->anim_frames[e->cur_frame_index];
}

void	update_player_frames(t_vec3 frm_mv, t_ent *e)
{
	if (frm_mv.x != 0)
	{
		e->movement.x = frm_mv.x * MV_DUR;
		if (frm_mv.x > 0)
			e->flip_x = 0;
		else
			e->flip_x = 1;
	}
	if (frm_mv.y != 0)
		e->movement.y = frm_mv.y * MV_DUR;
	if ((frm_mv.x == 0 && frm_mv.y == 0))
	{
		e->cur_frame = e->idl_frm[e->cur_frame_index];
		e->action = IDLE;
	}
	else if (!e->is_grounded)
		e->cur_frame = e->fly_frm[e->cur_frame_index];
	else if (frm_mv.x)
	{
		e->cur_frame = e->wlk_frm[e->cur_frame_index];
		e->action = WALK;
	}
	else
		e->cur_frame = e->fly_frm[0];
}

int	update_player2(t_ent *e, t_vec3 frm_mv, t_vec2 speed, t_md *mlx)
{
	if (e->is_grounded && e->movement.y > 0)
	{
		e->movement.y = 0;
		frm_mv.y = 0;
	}
	else if (!e->is_grounded && (!e->jet_sky_timer || \
		!mlx->key_prs[UP_KEY]) && mlx->time % 4 == 0)
		e->movement.y += 12;
	if (e->jump_timer > 0)
		e->jump_timer--;
	if (mlx->time % ANIM_REFRESH == 0)
	{
		e->cur_frame_index++;
		if (e->cur_frame_index > e->idle_frame_amount - 1)
			e->cur_frame_index = 0;
	}
	if (frm_mv.x || frm_mv.y)
		mlx->move_counter++;
	handle_movement(mlx, e, speed, get_vec2(mlx->t_len / 4, 0));
	update_player_frames(frm_mv, e);
	return (1);
}

int	update_player(t_md *md, t_vec3 new_mv, t_ent *plr)
{
	if (md->key_prs[LEFT_KEY] || md->key_prs[A_KEY])
		new_mv.x = -1;
	else if (md->key_prs[RIGHT_KEY] || md->key_prs[D_KEY])
		new_mv.x = 1;
	if (md->key_prs[DOWN_KEY] || md->key_prs[S_KEY])
		new_mv.y = 1;
	if ((md->key_prs[UP_KEY] || md->key_prs[W_KEY]) && plr->jet_sky_timer > 0)
	{
		new_mv.y -= ((100 - plr->jet_sky_timer) / 20);
		plr->jet_sky_timer -= 5;
	}
	else if (plr->is_grounded)
		plr->jet_sky_timer = 100;
	if (md->key_clicked == SPACE_KEY && plr->jumps)
	{
		play_random_sound(AU_FOOTSTEPS, 4, ".mp3");
		plr->jumps--;
		new_mv.y = -3;
	}
	if (plr->is_grounded)
		plr->jumps = 1;
	return (update_player2(plr, new_mv, get_vec2(50, 3), md));
}

int	update(t_md *md)
{
	md->plr.prv_pos.x += (md->plr.pos.x - md->plr.prv_pos.x) * .1;
	md->plr.prv_pos.y += (md->plr.pos.y - md->plr.prv_pos.y) * .1;
	update_env(md, 0);
	update_particles(md);
	if (md->plr.hp <= 0)
	{
		if (move_to_simple(&md->plr, get_vec3(md->plr.start_pos.x, \
			md->plr.start_pos.y, 0), 15))
			md->plr.hp = 5;
	}
	else
		update_player(md, get_vec3(0, 0, 0), &md->plr);
	if (md->plr.is_grounded && !md->ftstp_timer && \
		(md->key_prs[A_KEY] || md->key_prs[D_KEY] || md->key_prs[LEFT_KEY] || \
			md->key_prs[RIGHT_KEY]))
	{
		play_random_sound(AU_FOOTSTEPS, 4, ".mp3");
		md->ftstp_timer += 15;
	}
	if (md->ftstp_timer)
		md->ftstp_timer--;
	if (md->coin_au_timer)
		md->coin_au_timer--;
	return (1);
}
