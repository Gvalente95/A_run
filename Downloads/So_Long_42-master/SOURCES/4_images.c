/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_images.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 20:23:02 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void *rescale_image(void *mlx, void *img, int *original_width, int *original_height, int new_width, int new_height)
{
    void *scaled_img;
    int *src_data;
    int *scaled_data;
    int x, y;
    double x_ratio = (double)*original_width / new_width;
    double y_ratio = (double)*original_height / new_height;

    scaled_img = mlx_new_image(mlx, new_width, new_height);
    if (!scaled_img)
        return NULL;
    src_data = (int *)mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    scaled_data = (int *)mlx_get_data_addr(scaled_img, &(int){0}, &(int){0}, &(int){0});

    for (y = 0; y < new_height; y++)
    {
        for (x = 0; x < new_width; x++)
        {
            int src_x = (int)(x * x_ratio);
            int src_y = (int)(y * y_ratio);
            scaled_data[y * new_width + x] = src_data[src_y * *original_width + src_x];
        }
    }
	*original_height = new_height;
	*original_width = new_width;
    return scaled_img;
}

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
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i -1)
		{
			if (game_entities[j].pos.z < game_entities[j + 1].pos.z)
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
				// Load and rescale walk frames
				e->wlk_frm[i] = add_img(WLK_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->wlk_frm[i]) {
					printf("Original WLK frame size: %d x %d\n", e->size.x, e->size.y);
					
					// Rescale and replace with rescaled image
					void *rescaled_image = rescale_image(d->mlx, e->wlk_frm[i], &e->size.x, &e->size.y, rescaled_width, rescaled_height);
					if (rescaled_image) {
						// Optionally destroy original if not needed
						// mlx_destroy_image(d->mlx, e->wlk_frm[i]);
						e->wlk_frm[i] = rescaled_image;
						printf("Rescaled WLK frame size: %d x %d\n", e->size.x, e->size.y);

						// Flip the rescaled image if necessary
						e->wlk_frm_x[i] = flip_image_x(d->mlx, e->wlk_frm[i], rescaled_width, rescaled_height);

						// Display the rescaled image to the window for testing
						mlx_put_image_to_window(d->mlx, d->win, e->wlk_frm[i], 100, 100 + i * rescaled_height); // Adjust position for visibility
					}
				}
			}

			// Load and rescale idle frames
			if (IDLE_P[i] != NULL)
			{
				e->idl_frm[i] = add_img(IDLE_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->idl_frm[i]) {
					printf("Original IDLE frame size: %d x %d\n", e->size.x, e->size.y);
					
					// Rescale and replace with rescaled image
					void *rescaled_image = rescale_image(d->mlx, e->idl_frm[i], &e->size.x, &e->size.y, rescaled_width, rescaled_height);
					if (rescaled_image) {
						// Optionally destroy original if not needed
						// mlx_destroy_image(d->mlx, e->idl_frm[i]);
						e->idl_frm[i] = rescaled_image;
						printf("Rescaled IDLE frame size: %d x %d\n", e->size.x, e->size.y);

						// Flip the rescaled image if necessary
						e->idl_frm_x[i] = flip_image_x(d->mlx, e->idl_frm[i], rescaled_width, rescaled_height);

						// Display the rescaled image to the window for testing
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
