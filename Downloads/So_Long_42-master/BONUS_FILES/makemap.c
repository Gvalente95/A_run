/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:04:14 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 18:55:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HEADERS/header.h"

int	main(int argc, char **argv)
{
	char	*new_map;
	FILE	*map_file;
	t_vec2	map_size;
	int		solvable;

	map_size.x = r_range(5, 50);
	map_size.y = r_range(5, 50);
	if (argc >= 3)
	{
		map_size.x = ft_atoi(argv[1]);
		map_size.y = ft_atoi(argv[2]);
	}
	solvable = 1;
	if (argc == 4)
		solvable = ft_atoi(argv[3]);
	if (solvable == 2)
		new_map = get_empty_map(map_size);
	else
		new_map = get_new_map(map_size.x, map_size.y, \
			solvable);
	map_file = fopen("randomap.ber", "w");
	ft_printf("MAP GENERATED\n%s", new_map);
	fprintf(map_file, "%s", new_map);
	free(new_map);
	return (0);
}
