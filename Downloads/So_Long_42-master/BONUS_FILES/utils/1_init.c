/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:16:57 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 17:04:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	set_type_values(t_md *md, t_ent *e, t_ent_type type)
{
	if (type == portal)
		set_vec3(&e->pos, e->pos.x - md->t_len / 2, e->pos.y - \
			md->t_len / 2, 5);
	else if (type == wall)
		e->hp = 3;
	else if (e->type == coin)
	{
		e->base_pos.y += md->t_len / 3;
		e->pos.x += md->t_len / 3;
	}
}

t_ent	*init_entity(t_md *md, void *path, t_vec3 pos, \
	t_vec3 values)
{
	t_ent	*e;

	e = malloc(sizeof(t_ent));
	if (!e)
		return (NULL);
	set_vec3(&e->pos, pos.x * md->t_len, pos.y * md->t_len, pos.z);
	set_vec3(&e->prv_pos, e->pos.x, e->pos.y, e->pos.z);
	set_vec2(&e->foll_ofs, r_range(-10, 10), r_range(-5, 5));
	set_vec3(&e->movement, 0, 0, 0);
	e->is_grounded = 1;
	e->jumps = 2;
	e->is_active = 1;
	e->dir = r_range(0, 4);
	e->hp = 1;
	e->foll_spd = r_range(5, 7);
	e->cur_frame_index = r_range(0, pos.z - 1);
	e->frames_amount = values.z;
	e->jet_sky_timer = 0;
	e->hurt_timer = 0;
	e->base_pos = e->pos;
	e->type = values.y;
	handle_entity_frames(md, e, path, get_vec2(values.x, values.x));
	e->cur_frame = e->anim_frames[r_range(0, e->frames_amount - 1)];
	set_type_values(md, e, values.y);
	return (e);
}

int	init_player(t_md *md, char *path, t_vec3 pos)
{
	t_ent	*plr;

	plr = &md->plr;
	plr->type = player;
	plr->is_grounded = 0;
	plr->flip_x = 0;
	plr->jet_sky_timer = 0;
	plr->jumps = 2;
	plr->is_active = 1;
	plr->hurt_timer = 0;
	plr->cur_frame_index = 0;
	set_vec3(&plr->pos, pos.x * md->t_len, pos.y * md->t_len, 0);
	set_vec2(&plr->start_pos, pos.x * md->t_len, pos.y * md->t_len);
	set_vec3(&plr->movement, 0, 0, 0);
	set_vec2(&plr->size, md->t_len, md->t_len);
	init_player_frames(md, path, plr);
	return (1);
}

int	init_mlx(t_md *md)
{
	int	i;

	i = -1;
	while (++i < 512)
		md->key_prs[i] = 0;
	md->mlx = mlx_init();
	md->bgrnd = NULL;
	md->key = NULL;
	md->exit = NULL;
	md->images = NULL;
	md->all_images = NULL;
	md->env_images = NULL;
	md->index = 0;
	md->mouse_pressed = 0;
	md->mouse_clicked = 0;
	md->key_clicked = -1;
	md->images_len = 0;
	md->time = 0;
	md->move_counter = 0;
	md->ftstp_timer = 0;
	md->coins_amount = 0;
	md->coin_paths = get_paths(AU_COINS, "", 4, ".mp3");
	md->ftstp_paths = get_paths(AU_FOOTSTEPS, "", 4, ".wav");
	return (1);
}
