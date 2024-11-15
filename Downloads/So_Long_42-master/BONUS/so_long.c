/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:37:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/14 21:48:46 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"
#include <signal.h>

int	update_and_render(t_md *md)
{
	render(md);
	if (md->key_clicked == M_KEY)
		load_new_level(md);
	update_mouse(md);
	update(md);
	reset_mlx_values(md);
	if (!is_audio_playing(md->background_au))
		md->background_au = play_sound("audio_files/background.mp3", 1);
	md->time++;
	return (0);
}

void	init_background(t_md *md, t_vec2 size)
{
	t_vec2		bg_size;

	set_vec2(&bg_size, 0, 0);
	md->bg_col = mlx_new_image(md->mlx, size.x * md->t_len, size.y * md->t_len);
	md->background_img = mlx_png_file_to_image(md->mlx, \
		"PNG/BACKGROUND/2.png", &bg_size.x, &bg_size.y);
	md->background_img = scale_img(md->mlx, md->background_img, &bg_size, \
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
	init_background(md, md->map.size);
	get_ents_from_map(md, 0);
	sort_ents_by_z(md->images, md->images_len - 1);
	init_mouse(md);
	md->map.coins_amount = md->coins_amount;
	md->plr.hp = 5;
	md->has_key = 0;
}

int	main(int argc, char **argv)
{
	t_md		md;

	md.win = NULL;
	srand(time(0));
	init_mlx(&md);
	if (argc == 2)
		load_valid_map(argv[1], &md, NULL, get_vec2(0, 0));
	init_game(&md);
	md.background_au = play_sound("audio_files/background.mp3", 1);
	mlx_hook(md.win, KEY_PRESS, 0, handle_key_press, &md);
	mlx_hook(md.win, KEY_RELEASE, 0, handle_key_release, &md);
	mlx_loop_hook(md.mlx, (int (*)())update_and_render, &md);
	mlx_loop(md.mlx);
	stop_sound(md.background_au);
	return (0);
}
