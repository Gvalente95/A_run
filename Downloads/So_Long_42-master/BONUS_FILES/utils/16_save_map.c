/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_save_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:11:18 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 06:23:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	sort_coordinates(t_vec3 *coordinates, int len)
{
	int		i;
	int		j;
	t_vec3	tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if ((coordinates[j].y > coordinates[j + 1].y) || \
				(coordinates[j].y == coordinates[j + 1].y && \
					coordinates[j].x > coordinates[j + 1].x))
			{
				tmp = coordinates[j];
				coordinates[j] = coordinates[j + 1];
				coordinates[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	add_position(t_md *md, t_ent *ent, t_vec3 *positions, int *count)
{
	t_vec2	grid_p;
	int		j;
	int		is_duplicate;
	t_vec3	map_coord;

	map_coord = get_grid_pos(md, ent->pos);
	grid_p = get_vec2(map_coord.x / md->t_len, map_coord.y / md->t_len);
	if (grid_p.x >= md->map.size.x || grid_p.y >= md->map.size.y)
		return (1);
	is_duplicate = 0;
	j = -1;
	while (++j < *count)
	{
		if (positions[j].x == grid_p.x && positions[j].y == grid_p.y)
		{
			is_duplicate = 1;
			break ;
		}
	}
	if (!is_duplicate)
	{
		set_vec3(&positions[*count], grid_p.x, grid_p.y, (int)ent->type);
		(*count)++;
	}
	return (1);
}

t_vec3	*get_coordinates(t_md *md, t_ent **ents, int len)
{
	int		i;
	int		count;
	t_vec3	*positions;

	positions = malloc(sizeof(t_vec3) * len);
	if (!positions)
		return (NULL);
	count = 0;
	i = 0;
	while (i < len && ents[i])
	{
		if (add_position(md, ents[i], positions, &count))
			i++;
	}
	sort_coordinates(positions, count);
	return (positions);
}

void	write_to_file(t_md *md, t_vec3 *positions, int len, FILE *file)
{
	t_vec2	pos;
	int		i;
	char	*characters;

	characters = ft_strdup(TYPESTR);
	i = 0;
	pos.y = 0;
	while (pos.y < md->map.size.y)
	{
		pos.x = 0;
		while (pos.x < md->map.size.x)
		{
			if (i < len && pos.x == positions[i].x && pos.y == positions[i].y)
				fprintf(file, "%c", characters[positions[i++].z]);
			else
				fprintf(file, "0");
			pos.x++;
		}
		fprintf(file, "\n");
		pos.y++;
	}
	free(characters);
}

char	*store_map_name(t_md *md)
{
	char	*x_size;
	char	*y_size;
	char	*size;
	char	*size_part_0;

	x_size = ft_itoa(md->map.size.x);
	y_size = ft_itoa(md->map.size.y);
	size_part_0 = ft_strjoin(x_size, "x");
	size = ft_strjoin(size_part_0, y_size);
	free(x_size);
	free(y_size);
	free(size_part_0);
	return (size);
}
int	save_to_file(t_md *md)
{
	t_vec3		*positions;
	FILE		*file;
	char		*name;
	char		*with_ber;
	char		*with_folder_name;

	name = store_map_name(md);
	if (!name)
		return (0);
	with_ber = ft_strjoin(name, ".ber");
	with_folder_name = ft_strjoin("saved_maps/", with_ber);
	positions = get_coordinates(md, md->images, md->images_len);
	if (!positions)
		return (-1);
	file = fopen(with_folder_name, "w");
	if (!file)
	{
		free(positions);
		return (-1);
	}
	write_to_file(md, positions, md->images_len, file);
	ft_printf("map successfully saved to %s\n", with_folder_name);
	md->map.name = ft_strdup(with_folder_name);
	return (fclose(file), free(positions), free(with_folder_name), 0);
}
