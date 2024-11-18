/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:17:38 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 16:16:17 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

//UP LEFT DOWN RIGHT

void	compare_positions(t_vec2 pos_a, t_vec2 pos_b, int *best_x, int *best_y)
{
	if (pos_a.x > pos_b.x)
		*best_x = left;
	else
		*best_x = right;
	if (pos_a.y > pos_b.y)
		*best_y = up;
	else
		*best_y = down;
}

t_dir	get_dir_to_target(t_vec2 pos, t_vec2 posB, int valid_dirs[4], int i)
{
	t_dir	best_dir;
	int		selectable_neighbors[4];
	int		sel_count;
	int		best_x_dir;
	int		best_y_dir;

	sel_count = 0;
	compare_positions(pos, posB, &best_x_dir, &best_y_dir);
	if (abs(pos.x - posB.x) >= abs(pos.y - posB.y))
		best_dir = best_x_dir;
	else
		best_dir = best_y_dir;
	if (valid_dirs[best_dir])
		return (best_dir);
	if ((int)best_dir == best_x_dir && valid_dirs[best_y_dir])
		return (best_y_dir);
	while (i < 4)
	{
		if (valid_dirs[i])
			selectable_neighbors[sel_count++] = i;
		i++;
	}
	return (selectable_neighbors[r_range(0, sel_count - 1)]);
}

int	check_neighbors(char *buff, int ind, int end_index, int wd)
{
	int	valid_neighbors[4];
	int	valid_count;
	int	i;

	valid_count = 0;
	i = 0;
	while (i < 4)
		valid_neighbors[i++] = 0;
	if (ind - wd >= 0 && buff[ind - wd] != '1' && buff[ind - wd] != 'P')
		valid_neighbors[0] = ind - wd;
	if (ind % wd > 0 && buff[ind - 1] != '1' && buff[ind - 1] != 'P')
		valid_neighbors[1] = ind - 1;
	if (ind + wd < wd * wd && buff[ind + wd] != '1' && buff[ind + wd] != 'P')
		valid_neighbors[2] = ind + wd;
	if (ind % wd < wd - 1 && buff[ind + 1] != '1' && buff[ind + 1] != 'P')
		valid_neighbors[3] = ind + 1;
	i = 0;
	while (i < 4)
		if (valid_neighbors[i++] != 0)
			valid_count++;
	if (valid_count > 0)
		return (valid_neighbors[get_dir_to_target(get_vec2(ind % wd, ind / wd), \
			get_vec2(end_index % wd, end_index / wd), valid_neighbors, 0)]);
	return (0);
}

int	propagate_search(t_vec2 *indexes, char *buff, int line_width)
{
	int		check_x;
	int		prev_x_positions[90000];
	int		prv_positions_index;

	prv_positions_index = 0;
	while (indexes->x != indexes->y)
	{
		check_x = check_neighbors(buff, indexes->x, indexes->y, line_width);
		if (check_x)
		{
			prev_x_positions[prv_positions_index++] = indexes->x;
			indexes->x = check_x;
			if (buff[indexes->x] == 'E')
				return (1);
			buff[indexes->x] = 'P';
		}
		else
		{
			if (prv_positions_index > 0)
				indexes->x = prev_x_positions[--prv_positions_index];
			else
				return (0);
		}
	}
	return (0);
}

void	load_valid_map(char *file_path, t_md *md, char *buffer, t_vec2	pos)
{
	int		fd;
	t_vec2	size;

	if (check_path_format(file_path))
		close_and_quit("Error\nWrong path extension.", -1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		close_and_quit("Error\nEmpty file.", fd);
	buffer = get_map_buffer(fd);
	if (contain('P', buffer) != 1 || contain('E', buffer) != 1)
		close_and_quit("Error\nWrong 'P'/'E' amount.", fd);
	if (contain('C', buffer) < 1)
		close_and_quit("Error\n'C' amount.", fd);
	size = get_map_dimensions(buffer, 0, 0, get_vec2(0, 0));
	if (size.x < 3 || size.y < 3 || size.x > 5000 || size.y > 5000)
		close_and_quit("Error\nMap dimensions.", fd);
	md->map.size = get_vec2(size.x, size.y);
	md->map.buffer = ft_strdup(buffer);
	md->map.len = ft_strlen(buffer);
	pos = get_indexes(buffer);
	if (!propagate_search(&pos, buffer, md->map.size.x + 1))
		close_and_quit("Error\nNo path.", fd);
	verify_map_borders(md->map.buffer, size.x, size.y);
	close(fd);
}
