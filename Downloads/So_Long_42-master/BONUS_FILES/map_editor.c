/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:00:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 17:04:00 by giuliovalen      ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_md	md;

	md.win = NULL;
	md.save_mode = 0;
	srand(time(0));
	init_mlx(&md);
	if (argc != 2)
		argv[1] = ft_strdup("maps/default.ber");
	load_map(argv[1], &md, NULL);
	md.map.name = ft_strdup(argv[1]);
	md.plr.fly_frm = NULL;
	md.plr.idl_frm = NULL;
	md.plr.wlk_frm = NULL;
	init_game(&md);
	load_images(&md);
	if (md.images && md.images_len)
		rescale_coin_images(&md);
	md.selected = copy_ent(md.all_images[0]);
	mlx_hook(md.win, KEY_PRESS, 0, handle_key_press, &md);
	mlx_hook(md.win, KEY_RELEASE, 0, handle_key_release, &md);
	mlx_loop_hook(md.mlx, (int (*)())update_editor, &md);
	return (mlx_loop(md.mlx), 0);
}
