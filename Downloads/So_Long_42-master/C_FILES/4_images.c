/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_images.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/10 23:41:45 by giuliovalen      ###   ########.fr       */
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

void	*get_image_copy(t_mlx_data *mlx_ptr, void *src, t_Vec2 src_size)
{
	void 	*dest;
	
	int		*src_addr;
	int		*dest_addr;
	int		bpp;
	int		src_line_length;
	int		dest_line_length;
	int		endian;
	int		y;
	int		x;
	
	dest = mlx_new_image(mlx_ptr, src_size.x, src_size.y);
	if (dest == NULL)
	{
		printf("DEST FAILED\n");
		return (NULL);
	}
	src_addr = (int *)mlx_get_data_addr(src, &bpp, &src_line_length, &endian);
	dest_addr = (int *)mlx_get_data_addr(dest, &bpp, &dest_line_length, &endian);
	y = 0;
	while (y < src_size.y)
	{
		x = 0;
		while (x < src_size.x)
		{
			int src_pixel_index = (y * src_line_length / 4) + x;
			int dest_pixel_index = (y * dest_line_length / 4) + x;
			dest_addr[dest_pixel_index] = src_addr[src_pixel_index];
			x++;
		}
		y++;
	}
	return (dest);
}

void    my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
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
