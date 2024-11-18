/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:16:57 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 16:44:33 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

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

void	init_bgrnd(t_md *md, t_vec2 size)
{
	t_vec2		bg_size;

	set_vec2(&bg_size, 0, 0);
	md->bg_col = mlx_new_image(md->mlx, size.x * md->t_len, size.y * md->t_len);
	md->bgrnd_img = mlx_png_file_to_image(md->mlx, \
		"PNG/bgrnd/2.png", &bg_size.x, &bg_size.y);
	md->bgrnd_img = scale_img(md->mlx, md->bgrnd_img, &bg_size, \
		get_vec2(size.x * md->t_len, (size.y + 1) * md->t_len));
	md->addr = mlx_get_data_addr(md->bg_col, &md->bits_per_pixel, \
		&md->line_length, &md->endian);
}

void	init_game(t_md *md)
{
	int	win_width;
	int	tile_width;
	int	tile_height;
	int	required_width;

	win_width = WIN_W;
	tile_width = (int)((float)WIN_W / md->map.size.x + 0.5);
	tile_height = (int)((float)WIN_H / md->map.size.y + 0.5);
	md->t_len = tile_height;
	if (tile_width < tile_height)
		md->t_len = tile_width;
	required_width = md->t_len * md->map.size.x;
	if (required_width != WIN_W)
		win_width = required_width;
	if (md->win)
		mlx_destroy_window(md, md->win);
	md->win = mlx_new_window(md->mlx, win_width, \
	md->t_len * md->map.size.y, "g");
	init_bgrnd(md, md->map.size);
	get_ents_from_map(md, 0);
	sort_ents_by_z(md->images, md->images_len - 1);
	init_mouse(md);
	md->map.coins_amount = md->coins_amount;
	md->plr.hp = 5;
	md->has_key = 0;
}
