/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_images.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 15:44:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	copy_image_data(void *mlx, void *src, void *dest, t_Vec2 size)
{
    (void)mlx;
	int		*src_addr;
	int		*dest_addr;
	int		bpp;
	int		src_line_length;
	int		dest_line_length;
	int		endian;
	int		y;
	int		x;

	src_addr = (int *)mlx_get_data_addr(src, &bpp, &src_line_length, &endian);
	dest_addr = (int *)mlx_get_data_addr(dest, &bpp, &dest_line_length, &endian);
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			int src_pixel_index = (y * src_line_length / 4) + x;
			int dest_pixel_index = (y * dest_line_length / 4) + x;
			dest_addr[dest_pixel_index] = src_addr[src_pixel_index];
			x++;
		}
		y++;
	}
}

void    my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void swap_game_entities(t_ent *a, t_ent *b)
{
    t_ent temp = *a;
    *a = *b;
    *b = temp;
}

void sort_game_entities_by_z_pos(t_ent *game_entities, int count)
{
	int i;
	int	j;

	
	i = -1;
	j = -1;
	while (++i < count - 1)
	{
		while (++j < count - i -1)
		{
			if (game_entities[j].pos.z > game_entities[j + 1].pos.z)
                swap_game_entities(&game_entities[j], &game_entities[j + 1]);
		}
	}
}

void *add_img(char *relative_path, int *width, int *height, void *mlx)
{
    void *img;

    if (!relative_path) {
        ft_printf("Tried to add image with null path\n");
        return NULL;
    }
    if (!mlx) {
        ft_printf("Error: mlx instance is NULL\n");
        return NULL;
    }
    img = mlx_png_file_to_image(mlx, relative_path, width, height);
    if (!img) {
        printf("ERROR: Failed to load image at path: %s\n", relative_path);
        return NULL;
    }
    //printf("Image loaded successfully from path: %s, Width: %d, Height: %d\n", relative_path, *width, *height);
    return img;
}

int	set_entity_frames(t_mlx_data *d, t_ent *e, char **WLK_P, char **IDLE_P)
{
	int	i;

	if (WLK_P != NULL)
	{
		i = -1;
		while (++i < e->walk_frame_amount)
		{
			if (WLK_P[i] != NULL)
			{
				e->wlk_frm[i] = add_img(WLK_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->wlk_frm[i] != NULL)
					e->wlk_frm_x[i] = flip_image_x(d->mlx, e->wlk_frm[i], e->size.x, e->size.y);
			}
			if (IDLE_P[i] != NULL)
			{
				e->idl_frm[i] = add_img(IDLE_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->idl_frm[i] != NULL)
					e->idl_frm_x[i] = flip_image_x(d->mlx, e->idl_frm[i], e->size.x, e->size.y);
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