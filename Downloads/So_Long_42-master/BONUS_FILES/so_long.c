/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:37:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/20 21:48:23 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HEADERS/header.h"
#include <signal.h>

int	update_and_render(t_md *md)
{
	if (!is_audio_playing(md->bgrnd_au))
		md->bgrnd_au = play_sound("BONUS_FILES/audio_files/bgrnd.mp3", 1);
	render(md);
	if (md->key_clicked == M_KEY)
		load_new_level(md);
	update_mouse(md);
	update(md);
	reset_mlx_values(md);
	md->time++;
	return (0);
}

int	main(int argc, char **argv)
{
	t_md		md;

	md.win = NULL;
	srand(time(0));
	init_mlx(&md);
	if (argc != 2)
		close_and_quit("Error\nMap not given as argument", -1);
	load_valid_map(argv[1], &md, NULL, get_vec2(0, 0));
	init_game(&md);
	load_env_elements(&md);
	md.bgrnd_au = play_sound("BONUS_FILES/audio_files/bgrnd.mp3", 1);
	mlx_hook(md.win, KEY_PRESS, 0, handle_key_press, &md);
	mlx_hook(md.win, KEY_RELEASE, 0, handle_key_release, &md);
	mlx_loop_hook(md.mlx, (int (*)())update_and_render, &md);
	mlx_loop(md.mlx);
	stop_sound(md.bgrnd_au);
	return (0);
}
