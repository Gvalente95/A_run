/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:08:31 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 16:48:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	update_mob_entity(t_ent *e, t_md *md)
{
	t_ent	*ent_at_pos;
	t_vec3	new_pos;

	new_pos = e->pos;
	{
		if (e->dir == up)
			new_pos.y -= md->t_len;
		if (e->dir == down)
			new_pos.y += md->t_len;
		if (e->dir == left)
			new_pos.x -= md->t_len;
		if (e->dir == right)
			new_pos.x += md->t_len;
	}
	ent_at_pos = get_ent_simple(get_vec2(new_pos.x, new_pos.y), \
		md->images);
	if (!ent_at_pos)
	{
		set_vec3(&e->pos, new_pos.x, new_pos.y, e->pos.z);
		increment_frame(e);
	}
	else
		e->dir = r_range(0, 4);
}

void	handle_player_collision(t_md *md, t_ent *plr, \
	t_ent *col, t_vec2 new_pos)
{
	if (col->type != wall)
		set_vec3(&plr->pos, new_pos.x, new_pos.y, plr->pos.z);
	if (col->type == coin)
	{
		md->coins_amount--;
		col->is_active = 0;
		col->hp = 0;
	}
	if (col->type == mob)
	{
		free_md(md);
		exit(0);
	}
}

int	update_player(t_md *md, t_ent *plr, t_vec2 new_pos)
{
	t_ent	*ent_at_new_pos;

	set_vec2(&new_pos, plr->pos.x, plr->pos.y);
	if (md->key_clicked == LEFT_KEY || md->key_clicked == A_KEY)
		new_pos.x -= md->t_len;
	else if (md->key_clicked == RIGHT_KEY || md->key_clicked == D_KEY)
		new_pos.x += md->t_len;
	if (md->key_clicked == DOWN_KEY || md->key_clicked == S_KEY)
		new_pos.y += md->t_len;
	else if ((md->key_clicked == UP_KEY || md->key_clicked == W_KEY))
		new_pos.y -= md->t_len;
	ent_at_new_pos = get_ent_simple(new_pos, md->images);
	if (ent_at_new_pos != NULL)
		handle_player_collision(md, plr, ent_at_new_pos, new_pos);
	else
		set_vec3(&plr->pos, new_pos.x, new_pos.y, plr->pos.z);
	return (1);
}

void	increment_frame(t_ent *e)
{
	e->cur_frame_index++;
	if (e->cur_frame_index > e->frames_amount - 1 || \
		!e->anim_frames[e->cur_frame_index])
		e->cur_frame_index = 0;
	e->cur_frame = e->anim_frames[e->cur_frame_index];
}

int	update(t_md *md)
{
	t_ent	*e;
	int		i;
	int		has_moved;

	md->plr.prv_pos = md->plr.pos;
	update_player(md, &md->plr, get_vec2(0, 0));
	has_moved = (abs(md->plr.pos.x - md->plr.prv_pos.x) > 1 || \
		abs(md->plr.pos.y - md->plr.prv_pos.y) > 1);
	md->move_counter += has_moved;
	i = 0;
	while (md->images[i])
	{
		e = md->images[i];
		e->prv_pos = e->pos;
		if (e->type == mob && has_moved)
			update_mob_entity(e, md);
		if (!e->is_active)
		{
			i++;
			continue ;
		}
		if (md->images[i] == e)
			i++;
	}
	return (1);
}
