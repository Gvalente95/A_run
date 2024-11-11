/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_load_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:57:04 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/10 21:21:16 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void free_array(void **e, int amount)
{
	while (--amount >= 0)
		free(e[amount]);
	free(e);
}

t_ent **get_images_from_file(t_mlx_data *mlx_data, t_ent_type type, char *path, float scale_factor, int amount)
{
	t_Vec2 end_scale;
    t_ent **e;
    char *nbr;
    char *full_path;
    int i;

    e = malloc(sizeof(t_ent *) * (amount + 1)); 
    if (!e)
        return NULL;
	i = -1;
    while (++i < amount)
    {
        e[i] = malloc(sizeof(t_ent));
		set_Vec3(&e[i]->pos, 0, 0, 0);
        if (!e[i])
        {
            free_array((void **)e, i);
            return NULL;
        }
        nbr = ft_strjoin(ft_itoa(i), ".png");
        full_path = ft_strjoin(path, nbr);
        free(nbr);
        e[i]->cur_frame = add_img(full_path, &e[i]->size.x, &e[i]->size.y, mlx_data->mlx);
		if (scale_factor != 1)
		{
			end_scale.x = (int)e[i]->size.x * scale_factor;
			end_scale.y = (int)e[i]->size.y * scale_factor;
			if (end_scale.x > 1 && end_scale.y > 1)
				e[i]->cur_frame = rescale_image(mlx_data, e[i]->cur_frame, &e[i]->size.x, &e[i]->size.y, end_scale.x, end_scale.y);
		}
		e[i]->type = type;
		e[i]->frame_path = ft_strdup(full_path);
        free(full_path);
        if (!e[i]->cur_frame)
        {
            free(e[i]);
            e[i] = NULL;
            break;
        }
    }
    e[i] = NULL;
    return e;
}

void load_images(t_mlx_data *mlx_data)
{
    mlx_data->alll_images = malloc(sizeof(t_ent **) * (cat_count + 1));
    if (!mlx_data->alll_images)
        return;
    mlx_data->alll_images[0] = get_images_from_file(mlx_data, trees, TREES_SPRITES_PATH, .4, 7);
    mlx_data->alll_images[1] = get_images_from_file(mlx_data, deco, BUSH_SPRITES_PATH, .4, 10);
    mlx_data->alll_images[2] = get_images_from_file(mlx_data, wall, TILES_SPRITES_PATH, .8, 18);
    mlx_data->alll_images[3] = get_images_from_file(mlx_data, deco, ROAD_SPRITES_PATH, .2, 11);
    mlx_data->alll_images[4] = get_images_from_file(mlx_data, wall, WALL_SPRITES_PATH, .8, 11);
    mlx_data->alll_images[5] = get_images_from_file(mlx_data, wall, GROUND_SPRITES_PATH, .8, 11);
    mlx_data->alll_images[6] = get_images_from_file(mlx_data, background, BACKGROUND_SPRITE_PATH, .8, 11);
    mlx_data->alll_images[cat_count] = NULL;
	mlx_data->cur_category = 0;
}