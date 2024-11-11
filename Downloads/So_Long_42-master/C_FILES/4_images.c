/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_images.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/11 12:55:17 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	*rescale_image(void *mlx, void *img, t_vec2 *old_size, t_vec2 new_size)
{
	void	*scaled_img;
	int		*src_data;
	int		*scaled_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_vec2	cur_pos;
	double	x_ratio;
	double	y_ratio;

	x_ratio = (double)old_size->x / new_size.x;
	y_ratio = (double)old_size->y / new_size.y;

	scaled_img = mlx_new_image(mlx, new_size.x, new_size.y);
	if (!scaled_img)
		return (NULL);
	src_data = (int *)mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	scaled_data = (int *)mlx_get_data_addr(scaled_img, &bits_per_pixel, &size_line, &endian);
	
	cur_pos.y = 0;
	while (cur_pos.y < new_size.y)
	{
		cur_pos.x = 0;
		while (cur_pos.x < new_size.x)
		{
			int src_x = (int)(cur_pos.x * x_ratio);
			int src_y = (int)(cur_pos.y * y_ratio);
			scaled_data[cur_pos.y * new_size.x + cur_pos.x] = src_data[src_y * old_size->x + src_x];
			cur_pos.x++;
		}
		cur_pos.y++;
	}
	
	old_size->x = new_size.x;
	old_size->y = new_size.y;
	return (scaled_img);
}


void	*get_image_copy(t_mlx_data *mlx_ptr, void *src, t_vec2 src_size)
{
	void	*dest;
	int		*src_adr;
	int		*dst_adr;
	int		bpp;
	int		src_line_length;
	int		dest_line_length;
	int		endian;
	int		y;
	int		x;
	int 	src_pixel_index;
	int		dest_pixel_index;

	dest = mlx_new_image(mlx_ptr, src_size.x, src_size.y);
	if (dest == NULL)
	{
		printf("DEST FAILED\n");
		return (NULL);
	}
	src_adr = (int *)mlx_get_data_addr(src, &bpp, &src_line_length, &endian);
	dst_adr = (int *)mlx_get_data_addr(dest, &bpp, &dest_line_length, &endian);
	y = 0;
	while (y < src_size.y)
	{
		x = 0;
		while (x < src_size.x)
		{
			src_pixel_index = (y * src_line_length / 4) + x;
			dest_pixel_index = (y * dest_line_length / 4) + x;
			dst_adr[dest_pixel_index] = src_adr[src_pixel_index];
			x++;
		}
		y++;
	}
	return (dest);
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	*add_img(char *relative_path, int *width, int *height, void *mlx)
{
	void	*img;

	if (!relative_path)
	{
		ft_printf("Tried to add image with null path\n");
		return (NULL);
	}
	if (!mlx)
	{
		ft_printf("Error: mlx instance is NULL\n");
		return (NULL);
	}
	img = mlx_png_file_to_image(mlx, relative_path, width, height);
	if (!img)
	{
		printf("ERROR: Failed to load image at path: %s\n", relative_path);
		return (NULL);
	}
	return (img);
}
