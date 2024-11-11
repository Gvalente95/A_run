/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:04:14 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/11 06:28:46 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "../RESSOURCES/libft/libft.h"
int rand_range(int min, int max)
{
    if (min > max)
        return -1;
    return min + rand() % (max - min + 1);
}

void generate_map(int x_max, int y_max, int x_min, int y_min)
{
	FILE *map_file;
	int player_placed;
	int x;
	int y;
	int i;
	int map_len;
	int size[2];
	char c;
	char *buffer;

	map_file = fopen("randomap.ber", "w");
	size[0] = rand_range(x_min, x_max);
	size[1] = rand_range(y_min, y_max);
	buffer = malloc(size[1] * (size[0] + 1) + 1);
	map_len = size[0] * (size[1] + 1) + 1;
	player_placed = 0;
	i = 0;
	y = -1;
	while (++y < size[1])
	{
		x = -1;
		while (++x < size[0])
		{
			if (player_placed > 2)
				player_placed--;			
			if ((x == 0 || x == size[0]-1 || y == 0 || y == size[1] - 1) || rand_range(0, 20) == 0)
			{
				c = '1';
				if (!player_placed && y > 1 && buffer[i - size[0] - 1] && buffer[i - size[0] - 1] == '0')
				{
					buffer[i - size[0] - 1] = 'P';
					player_placed = 1;
				}
			}
			else if (rand_range(0, 2) == 0)
				c = 'C';
			else if (rand_range(0,2) == 0)
				c = 'T';
			else
				c = '0';
			buffer[i++] = c;
		}
		buffer[i++] = '\n';
	}
	buffer[i] = '\0';
	fprintf(map_file, "%s", buffer);
	printf("%s", buffer);
	fclose(map_file);
}

#include <time.h>
int main(int argc, char **argv)
{
	int args[4];

	int i;
	i = -1;
	while (++i < 4)
		args[i] = 5;
	while (argc > 1)
	{
		args[argc] = ft_atoi(argv[argc - 1]);
		argc--;
	}
	srand(time(0));
	generate_map(args[3], args[2], args[1], args[0]);
}
