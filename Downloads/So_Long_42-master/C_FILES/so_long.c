/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:37:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 23:19:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HEADERS/header.h"
#include <signal.h>

int	r_range(int min, int max)
{
	if (min > max)
		return (-1);
	return (min + rand() % (max - min + 1));
}

int	update_and_render(t_md *md)
{
	render(md);
	update(md);
	reset_mlx_values(md);
	md->time++;
	return (0);
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
	load_ents(md, 0, get_vec3(0, 0, 0));
	md->map.coins_amount = md->coins_amount;
	md->plr.hp = 5;
	md->has_key = 0;
}

int	main(int argc, char **argv)
{
	t_md		md;

	md.win = NULL;
	srand(time(0));
	init_mlx(&md, -1);
	if (argc != 2)
		close_and_quit("Error\nMap not given as argument", -1);
	load_valid_map(argv[1], &md, NULL, get_vec2(0, 0));
	init_game(&md);
	mlx_hook(md.win, KEY_PRESS, 0, handle_key_press, &md);
	mlx_hook(md.win, KEY_RELEASE, 0, handle_key_release, &md);
	mlx_loop_hook(md.mlx, (int (*)())update_and_render, &md);
	mlx_loop(md.mlx);
	return (0);
}
