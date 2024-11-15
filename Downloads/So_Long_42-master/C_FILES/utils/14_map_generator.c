/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_map_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:31:50 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/15 22:17:12 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "unistd.h"
#include <time.h>
#include "../../HEADERS/header.h"

int	contain(char c, char *arg)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (arg[i])
	{
		if (arg[i] == c)
			amount++;
		i++;
	}
	return (amount);
}

char	set_char(t_map *map, int solvable)
{
	int		is_border;

	is_border = (map->pos.x == 0 || map->pos.x == map->size.x - 1 \
		|| map->pos.y == 0 || map->pos.y == map->size.y - 1);
	if (is_border || r_range(0, 5) == 0 || \
		(!solvable && map->pos.y == map->size.y / 2))
	{
		if (!contain('P', map->buffer) && map->pos.y > 1 && \
			!is_border && map->buffer[map->pos.z - map->size.x - 1] == '0')
			map->buffer[map->pos.z - map->size.x - 1] = 'P';
		return ('1');
	}
	else if (map->pos.y == map->size.y - 2 && \
		!contain('E', map->buffer))
		return ('E');
	else if (r_range(0, 3) == 0 && contain('C', map->buffer) < map->coin_max)
		return ('C');
	else if (r_range(0, 9) == 0 && contain('M', map->buffer) < map->mob_max)
		return ('M');
	else if (r_range(0, 9) == 0 && contain('T', map->buffer) < 1)
		return ('T');
	else if (!contain('A', map->buffer))
		return ('A');
	return ('0');
}

char	*generate_map(t_map *map, int max_try, int solvable)
{
	if (map->tries_amount > max_try)
		return (NULL);
	map->buffer = malloc(map->size.y * (map->size.x + 1) + 1);
	map->len = map->size.y * (map->size.x + 1) + 1;
	map->pos.z = 0;
	map->pos.y = -1;
	while (++map->pos.y < map->size.y)
	{
		map->pos.x = -1;
		while (++map->pos.x < map->size.x)
			map->buffer[map->pos.z++] = set_char(map, solvable);
		map->buffer[map->pos.z++] = '\n';
	}
	map->buffer[map->pos.z] = '\0';
	if (!(contain('P', map->buffer) && contain('E', map->buffer) && \
		contain('1', map->buffer)))
	{
		map->tries_amount++;
		free(map->buffer);
		return (generate_map(map, max_try, solvable));
	}
	return (map->buffer);
}

char	*get_new_map(int width, int height, int solvable)
{
	char	*map_check;
	t_map	map;
	t_vec2	indexes;

	srand(time(0));
	map.size.x = width;
	map.size.y = height;
	map.coin_max = 50;
	map.mob_max = 50;
	map.tries_amount = 0;
	map.buffer = generate_map(&map, 500, solvable);
	if (!map.buffer || ft_strlen(map.buffer) <= 5)
		close_and_quit("Unable to make valid map", -1);
	indexes = get_indexes(map.buffer);
	map_check = ft_strdup(map.buffer);
	if (!propagate_search(&indexes, map_check, width + 1) && solvable)
	{
		free(map_check);
		return (get_new_map(width, height, solvable));
	}
	return (map.buffer);
}
