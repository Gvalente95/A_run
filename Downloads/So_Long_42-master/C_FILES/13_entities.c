/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_entities.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:03:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/10 19:38:47 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

t_ent *copy_ent(t_ent *e)
{
    t_ent *new_ent;
	
	new_ent = malloc(sizeof(t_ent));
    if (!new_ent)
        return NULL;
    ft_memcpy(new_ent, e, sizeof(t_ent));
	set_Vec3(&new_ent->pos, e->pos.x, e->pos.y, e->pos.z);
    return new_ent;
}

int set_entity_frames(t_mlx_data *d, t_ent *e, char **WLK_P, char **IDLE_P)
{
	int	i;
	int	rescaled_width = 40, rescaled_height = 40;

	if (WLK_P != NULL)
	{
		for (i = 0; i < e->walk_frame_amount; i++)
		{
			if (WLK_P[i] != NULL)
			{
				e->wlk_frm[i] = add_img(WLK_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->wlk_frm[i]) {					
					void *rescaled_image = rescale_image(d->mlx, e->wlk_frm[i], &e->size.x, &e->size.y, rescaled_width, rescaled_height);
					if (rescaled_image) {
						e->wlk_frm[i] = rescaled_image;
						e->wlk_frm_x[i] = flip_image_x(d->mlx, e->wlk_frm[i], rescaled_width, rescaled_height);
						mlx_put_image_to_window(d->mlx, d->win, e->wlk_frm[i], 100, 100 + i * rescaled_height);
					}
				}
			}
			if (IDLE_P[i] != NULL)
			{
				e->idl_frm[i] = add_img(IDLE_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->idl_frm[i]) {
					void *rescaled_image = rescale_image(d->mlx, e->idl_frm[i], &e->size.x, &e->size.y, rescaled_width, rescaled_height);
					if (rescaled_image) {
						e->idl_frm[i] = rescaled_image;
						e->idl_frm_x[i] = flip_image_x(d->mlx, e->idl_frm[i], rescaled_width, rescaled_height);
						mlx_put_image_to_window(d->mlx, d->win, e->idl_frm[i], 200, 100 + i * rescaled_height); // Adjust position for visibility
					}
				}
			}
		}
	}
	e->cur_frame = e->idl_frm[0];
	e->cur_frame_x = e->idl_frm_x[0];
	e->cur_frame_index = 0;
	e->jump_timer = 0;
	e->action = IDLE;
	return (1);
}

void swap_game_entities(t_ent *a, t_ent *b)
{
    t_ent temp = *a;
    *a = *b;
    *b = temp;
}

void sort_game_entities_by_z_pos(t_ent **game_entities, int count)
{
    int i;
	int j;
    int swapped;

    if (count <= 1)
        return;
	i = -1;
    while (++i < count - 1)
	{
        swapped = 0;
		j = -1;
		while (++j < count -i - 1)
		{
            if (game_entities[j] == NULL || game_entities[j + 1] == NULL)
                continue;
            if (game_entities[j]->pos.z < game_entities[j + 1]->pos.z)
			{
                swap_game_entities(game_entities[j], game_entities[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void set_ent_to_mouse(t_ent *ent, t_mlx_data *mlx_data)
{
	ent->movement.x = 0;
	ent->movement.y = 0;
	ent->pos.x = mlx_data->mouse_pos[0] - (ent->size.x / 2);
	ent->pos.y = mlx_data->mouse_pos[1] - (ent->size.y / 2);
}

void render_entity(t_mlx_data *mlx_data, t_ent *e)
{
	if (e->pos.x >= -e->size.x && e->pos.x <= WIN_W && \
			e->pos.y >= -e->size.y && e->size.y <= WIN_H)
		{
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, e->cur_frame, \
				e->pos.x, e->pos.y);	
		}
}

void render_array(t_mlx_data *mlx_data, t_ent **e, t_ent *selected)
{
	int insert_done;
	int i;

	insert_done = 0;
	i = -1;
	while (e[++i])
	{
		render_entity(mlx_data, e[i]);
		if (selected != NULL && !insert_done && e[i]->pos.z < selected->pos.z)
		{
			render_entity(mlx_data, selected);
			insert_done = 1;
		}
	}
	if (selected != NULL && !insert_done)
		render_entity(mlx_data, selected);
}

