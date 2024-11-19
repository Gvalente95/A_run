/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:39:27 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 06:05:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	init_player_frames(t_md *md, char *path, t_ent *e)
{
	char	**idl_frm;
	char	**wlk_frm;
	char	**fly_frm;

	e->walk_frame_amount = 2;
	e->idle_frame_amount = 2;
	idl_frm = get_paths(path, "IDLE_", 2, ".png");
	wlk_frm = get_paths(path, "WALK_", 2, ".png");
	fly_frm = get_paths(path, "FLY_", 2, ".png");
	e->wlk_frm = get_images(md, e, wlk_frm, e->size);
	e->idl_frm = get_images(md, e, idl_frm, e->size);
	e->fly_frm = get_images(md, e, fly_frm, e->size);
	e->cur_frame = e->idl_frm[0];
	e->frames_amount = 2;
	set_vec2(&md->plr.start_pos, e->pos.x, e->pos.y);
	e->cur_frame_index = 0;
}

void	handle_entity_frames(t_md *md, t_ent *e, void *path, t_vec2 scale)
{
	char	**frames;
	int		frames_amount;

	frames_amount = e->frames_amount;
	frames = get_paths(path, "", frames_amount, ".png");
	e->anim_frames = malloc(sizeof(void *) * (frames_amount + 1));
	if (!e->anim_frames)
		return ;
	e->frames_amount = -1;
	while (frames[++e->frames_amount] && e->frames_amount < frames_amount)
	{
		e->anim_frames[e->frames_amount] = add_img(frames[e->frames_amount], \
			&e->size.x, &e->size.y, md);
		if (!e->anim_frames[e->frames_amount])
			break ;
		e->anim_frames[e->frames_amount] = scale_img(md, \
			e->anim_frames[e->frames_amount], &e->size, scale);
	}
	free (frames);
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

	tile_width = (int)((float)WIN_W / md->map.size.x + 0.5);
	tile_height = (int)((float)WIN_H / md->map.size.y + 0.5);
	md->t_len = tile_height;
	if (tile_width < tile_height)
		md->t_len = tile_width;
	win_width = md->t_len * md->map.size.x;
	if (md->win)
		mlx_destroy_window(md, md->win);
	md->win = mlx_new_window(md->mlx, win_width, \
	md->t_len * md->map.size.y, "g");
	init_bgrnd(md, md->map.size);
	get_ents_from_map(md, 0, get_vec3(0, 0, 0));
	sort_ents_by_z(md->images, md->images_len - 1);
	init_mouse(md);
	md->map.coins_amount = md->coins_amount;
	md->plr.hp = 5;
	md->has_key = 0;
}
