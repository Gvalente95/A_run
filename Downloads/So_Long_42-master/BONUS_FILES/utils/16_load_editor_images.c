/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_load_editor_images.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:57:04 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 16:48:00 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

int	save_to_file(t_md *md, int len, char *file_path)
{
	char	*characters;
	t_ent	*ent;
	int		i;
	FILE	*file;

	file = fopen(file_path, "w");
	characters = ft_strdup(TYPESTR);
	i = 0;
	while (i < len)
	{
		ent = md->images[i];
		if (!ent)
			break ;
		fprintf(file, "%c", characters[ent->type]);
		i++;
	}
	fclose(file);
	free(characters);
	return (0);
}

t_ent	*set_new_image(t_md *md, t_ent_type type, char *path, t_vec2 size)
{
	t_ent	*e;

	e = malloc(sizeof(t_ent));
	if (!e)
		return (NULL);
	set_vec3(&e->pos, 0, 0, 0);
	e->cur_frame = mlx_png_file_to_image(md, path, &e->size.x, &e->size.y);
	e->cur_frame = scale_img(md, e->cur_frame, &e->size, size);
	free(path);
	e->type = type;
	set_vec3(&e->pos, 0, 0, 0);
	return (e);
}

t_ent	**get_images_from_file(t_md *md, t_ent_type type, \
	char *path, int amount)
{
	t_ent	**e;
	char	**p;
	int		i;

	p = get_paths(path, "", amount, ".png");
	e = malloc(sizeof(t_ent *) * (amount + 1));
	i = -1;
	while (++i < amount)
	{
		e[i] = set_new_image(md, type, p[i], get_vec2(md->t_len, md->t_len));
		if (!e[i])
		{
			free_array(e, i, 0);
			return (NULL);
		}
		if (!e[i]->cur_frame)
		{
			free(e[i]);
			break ;
		}
	}
	e[i] = NULL;
	free(p);
	return (e);
}

void	load_images(t_md *md)
{
	md->all_images = malloc(sizeof(t_ent **) * (CAT_COUNT + 1));
	if (!md->all_images)
		return ;
	md->all_images[0] = get_images_from_file(md, \
		env, TREES_SPR_PATH, 7);
	md->all_images[1] = get_images_from_file(md, \
		env, BUSH_SPR_PATH, 10);
	md->all_images[2] = get_images_from_file(md, tile, TILES_SPR_PATH, 18);
	md->all_images[3] = get_images_from_file(md, env, ROAD_SPR_PATH, 11);
	md->all_images[4] = get_images_from_file(md, wall, WALL_SPR_PATH, 11);
	md->all_images[5] = get_images_from_file(md, wall, GROUND_SPR_PATH, 11);
	md->all_images[6] = get_images_from_file(md, bgrnd, BGR_SPRITE_PATH, 11);
	md->all_images[CAT_COUNT] = NULL;
	md->cur_category = 0;
}
