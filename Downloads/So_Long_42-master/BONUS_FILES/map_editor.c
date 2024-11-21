/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:00:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 16:25:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HEADERS/header.h"

int	load_map(char *file_path, t_md *md, char *buffer)
{
	int		fd;
	t_vec2	size;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (0);
	buffer = get_map_buffer(fd, 0);
	size = get_map_dimensions(buffer, 0, 0, get_vec2(0, 0));
	md->map.size = get_vec2(size.x, size.y);
	md->map.buffer = ft_strdup(buffer);
	md->map.len = ft_strlen(buffer);
	close(fd);
	return (1);
}

void	rescale_coin_images(t_md *md)
{
	int		i;

	i = 0;
	while (md->images[i] && i < md->images_len)
	{
		if (md->images[i]->type == coin)
		{
			md->images[i]->cur_frame = \
				md->all_images[(int)md->images[i]->type]->cur_frame;
			md->images[i]->pos = get_grid_pos(md, md->images[i]->pos);
			md->images[i]->size = get_vec2(md->t_len, md->t_len);
		}
		i++;
	}
}

void	init_editor(t_md *md)
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
	load_images(md);
	init_bgrnd(md, md->map.size);
	load_ents_editor(md, 0, get_vec3(0, 0, 0));
	init_mouse(md);
	md->map.coins_amount = md->coins_amount;
	md->particles = NULL;
}

int	main(int argc, char **argv)
{
	t_md	md;

	md.win = NULL;
	md.save_mode = 0;
	srand(time(0));
	init_mlx(&md);
	if (argc != 2)
		argv[1] = ft_strdup("maps/default.ber");
	if (!load_map(argv[1], &md, NULL))
		close_and_quit("Error\nmap not found", -1);
	md.map.name = ft_strdup(argv[1]);
	md.plr.fly_frm = NULL;
	md.plr.idl_frm = NULL;
	md.plr.wlk_frm = NULL;
	md.plr.cur_frame = NULL;
	init_editor(&md);
	md.selected = copy_ent(md.all_images[0]);
	mlx_hook(md.win, KEY_PRESS, 0, handle_key_press, &md);
	mlx_hook(md.win, KEY_RELEASE, 0, handle_key_release, &md);
	mlx_loop_hook(md.mlx, (int (*)())update_editor, &md);
	return (mlx_loop(md.mlx), 0);
}
