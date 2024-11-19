/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_level_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:08:16 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 16:35:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	free_entity(t_ent *ent)
{
	if (ent != NULL)
	{
		free(ent);
		ent = NULL;
	}
}

void	free_array(t_ent **ents, int len, int i)
{
	while (i < len && ents[i])
		free_entity(ents[i++]);
	free(ents);
}

void	relaunch_program(const char *arg)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("./bonus");
	args[1] = ft_strdup(arg);
	args[2] = NULL;
	ft_printf("launching\n%s %s\n", args[0], args[1]);
	execvp(args[0], args);
	free(args[0]);
	free(args[1]);
	perror("execvp failed");
	exit(1);
}

void	get_new_map_ratio(t_map *map, int increment)
{
	float	aspect_ratio;

	aspect_ratio = (float)map->size.x / map->size.y;
	map->size.x += increment;
	map->size.y = (int)(map->size.x / aspect_ratio);
}

void	load_new_level(t_md *md)
{
	char	*map;
	FILE	*map_file;

	get_new_map_ratio(&md->map, 1);
	map = get_new_map(md->map.size.x, md->map.size.y, 1);
	if (!map)
	{
		perror("Error while generating new map\n");
		exit(0);
	}
	ft_printf("%s", map);
	usleep(500);
	map_file = fopen("randomap.ber", "w");
	fprintf(map_file, "%s", map);
	fclose(map_file);
	stop_sound(md->bgrnd_au);
	free(map);
	free_array(md->images, md->images_len, 0);
	relaunch_program("randomap.ber");
	exit(0);
}
