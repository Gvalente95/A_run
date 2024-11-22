/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:00:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 01:19:56 by giuliovalen      ###   ########.fr       */
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
	init_window(md);
	load_images(md);
	init_bgrnd(md, md->map.size);
	load_ents_editor(md, 0, get_vec3(0, 0, 0));
	init_mouse(md);
	md->map.coins_amount = md->coins_amount;
	md->particles = NULL;
}

char	*get_file_with_empty_map(char *argv1, char *argv2)
{
	FILE	*file;
	t_vec2	size;
	char	*new_map;
	char	*new_map_x_name;
	char	*new_map_name;

	size = get_vec2(ft_atoi(argv1), ft_atoi(argv2));
	new_map = get_empty_map(size);
	if (!new_map)
		close_and_quit("Error\nFailed to genereate empty map", -1);
	new_map_x_name = ft_strjoin(argv1, "x");
	if (!new_map_x_name)
		close_and_quit("Error\nFailed to allocate memory for empty map", -1);
	new_map_name = ft_strjoin(new_map_x_name, argv2);
	free(new_map_x_name);
	if (!new_map_name)
		close_and_quit("Error\nFailed to join map name", -1);
	file = fopen(new_map_name, "w");
	if (!file)
		close_and_quit("Error\nFailed to open file for writing.", -1);
	fprintf(file, "%s", new_map);
	fclose(file);
	free(new_map);
	return (new_map_name);
}

int	main(int argc, char **argv)
{
	t_md	md;

	md.win = NULL;
	md.save_mode = 0;
	srand(time(0));
	init_mlx(&md, -1);
	if (argc <= 1 || argc > 3)
		argv[1] = ft_strdup("maps/default.ber");
	else if (argc == 3)
		argv[1] = get_file_with_empty_map(argv[1], argv[2]);
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
