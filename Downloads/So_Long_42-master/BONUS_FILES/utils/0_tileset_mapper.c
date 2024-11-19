/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_tileset_mapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:45:29 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 14:18:44 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

char	*generate_tile_path(char *base_path, char *suffix, int index)
{
	char	*index_str;
	char	*path_with_suffix;
	char	*complete_path;

	index_str = ft_itoa(index);
	if (!index_str)
		return (NULL);
	path_with_suffix = ft_strjoin(base_path, suffix);
	if (!path_with_suffix)
	{
		free(index_str);
		return (NULL);
	}
	complete_path = ft_strjoin(path_with_suffix, index_str);
	free(index_str);
	free(path_with_suffix);
	if (!complete_path)
		return (NULL);
	return (ft_strjoin(complete_path, ".png"));
}

void	**get_tiles_for_pos(t_md *md, char *base_path, char *suffix, int amount)
{
	t_vec2	size;
	char	*complete_path;
	void	**tils;
	int		i;

	tils = malloc(amount * sizeof(void *));
	if (!tils)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		complete_path = generate_tile_path(base_path, suffix, i);
		if (!complete_path)
		{
			free(tils);
			return (NULL);
		}
		tils[i] = mlx_png_file_to_image(md, complete_path, &size.x, &size.y);
		tils[i] = scale_img(md, tils[i], &size, get_vec2(md->t_len, md->t_len));
		free(complete_path);
		i++;
	}
	return (tils);
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
	t_vec2	max;

	max = get_vec2(r_range(0, 2), r_range(0, 2));
	correct_tile = NULL;
	if (pos.x == 0 && pos.y == 0)
		correct_tile = images[LEFT_UP][0];
	else if (pos.x == md->map.size.x - 1 && pos.y == 0)
		correct_tile = images[RIGHT_UP][0];
	else if (pos.x == md->map.size.x - 1 && pos.y == md->map.size.y - 1)
		correct_tile = images[DOWN_RIGHT][0];
	else if (pos.x == md->map.size.x - 1)
		correct_tile = images[RIGHT][r_range(0, max.x)];
	else if (pos.x == 0)
		correct_tile = images[LEFT][r_range(0, max.x)];
	else if (pos.y == 0)
		correct_tile = images[UP][r_range(0, max.y)];
	else if (pos.y == md->map.size.y - 1)
		correct_tile = images[DOWN][r_range(0, max.y)];
	else if (pos.x < md->map.size.x / 10 || pos.y < md->map.size.y / 10 \
		|| pos.y > md->map.size.y - md->map.size.y / 10 || pos.x > \
			md->map.size.x - md->map.size.x / 10)
		correct_tile = images[CENTER][r_range(0, max.y)];
	if (correct_tile != NULL)
		e->cur_frame = correct_tile;
}

void	remap_wall_entities(t_md *md, t_ent *e, char *png_path, t_vec3 pos)
{
	void	***tile_images;

	if (e->type != wall)
		return ;
	tile_images = NULL;
	tile_images = get_tiles_images(md, png_path, 3);
	assign_tile(md, e, tile_images, pos);
	free(tile_images);
}
