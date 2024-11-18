/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_tileset_mapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:45:29 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 16:30:27 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void    **get_tiles_for_pos(t_md *md, char *png_path, char *suffix, int amount)
{
	t_vec2	size;
	char	*full_path;
	char	*index_str;
	char	*complete_path;
	char	*path_with_format;
	void	**tiles;
	int		i;

	tiles = malloc(amount * sizeof(void *));
	if (!tiles)
		return (NULL);
	full_path = ft_strjoin(png_path, suffix);
	if (!full_path)
	{
		free(tiles);
		return (NULL);
	}
	i = 0;
	while (i < amount)
	{
		index_str = ft_itoa(i);
		complete_path = ft_strjoin(full_path, index_str);
		path_with_format = ft_strjoin(complete_path, ".png");
		free(index_str);
		free(complete_path);
		tiles[i] = mlx_png_file_to_image(md, path_with_format, &size.x, &size.y);
		tiles[i] = scale_img(md, tiles[i], &size, get_vec2(md->t_len, md->t_len));
		free(path_with_format);
		i++;
	}
	free(full_path);
	return (tiles);
}

void	***get_tiles_images(t_md *md, char *path, int set_width)
{
	void	***tiles;

	tiles = malloc(9 * sizeof(void **));
	if (!tiles)
		return (NULL);
	tiles[0] = get_tiles_for_pos(md, path, "lu", 1);
	tiles[1] = get_tiles_for_pos(md, path, "u", set_width);
	tiles[2] = get_tiles_for_pos(md, path, "ru", 1);
	tiles[3] = get_tiles_for_pos(md, path, "l", set_width);
	tiles[4] = get_tiles_for_pos(md, path, "c", set_width);
	tiles[5] = get_tiles_for_pos(md, path, "r", set_width);
	tiles[6] = get_tiles_for_pos(md, path, "dl", 1);
	tiles[7] = get_tiles_for_pos(md, path, "d", set_width);
	tiles[8] = get_tiles_for_pos(md, path, "dr", 1);
	return (tiles);
}

void	assign_tile(t_md *md, t_ent *e, void ***images, t_vec3 pos)
{
	void	*correct_tile;
	int		max;
	int		max_x;
	int		max_y;

	max = 2;
	max_x = pos.x > max ? max : pos.x;
	max_y = pos.y > max ? max : pos.y;
	correct_tile = images[CENTER][r_range(0, max)];
	if (pos.x == 0 && pos.y == 0)
		correct_tile = images[LEFT_UP][0];
	else if (pos.x == md->map.size.x - 1 && pos.y == 0)
		correct_tile = images[RIGHT_UP][0];
	else if (pos.x == md->map.size.x - 1 && pos.y == md->map.size.y - 1)
		correct_tile = images[DOWN_RIGHT][0];
	else if (pos.x == md->map.size.x - 1)
		correct_tile = images[RIGHT][r_range(0, max_y)];
	else if (pos.x == 0)
		correct_tile = images[LEFT][r_range(0, max_y)];
	else if (pos.y == 0)
		correct_tile = images[UP][r_range(0, max_x)];
	else if (pos.y == md->map.size.y - 1)
		correct_tile = images[DOWN][r_range(0, max_x)];
	if (correct_tile != NULL)
		e->cur_frame = correct_tile;
}

void	remap_wall_entities(t_md *md, t_ent *e, char *png_path, t_vec3 pos)
{
	(void)pos;
	void	***tile_images;

	if (e->type != wall)
		return ;
	tile_images = NULL;
	tile_images = get_tiles_images(md, png_path, 3);

	assign_tile(md, e, tile_images, pos);
	free(tile_images);
}
