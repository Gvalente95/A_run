/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_images.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 06:38:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

char	**get_paths(char *path, char *prefix, int amount, char *suffix)
{
	int		i;
	char	*num_value;
	char	**frames_path;
	char	*with_prefix;
	char	*with_suffix;

	frames_path = malloc(sizeof(char *) * (amount + 1));
	if (!frames_path)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		num_value = ft_itoa(i);
		with_prefix = ft_strjoin(prefix, num_value);
		free(num_value);
		with_suffix = ft_strjoin(with_prefix, suffix);
		free(with_prefix);
		frames_path[i] = ft_strjoin(path, with_suffix);
		free(with_suffix);
		i++;
	}
	frames_path[i] = NULL;
	return (frames_path);
}

void	*scale_img(void *mlx, void **img, t_vec2 *old_size, t_vec2 new_size)
{
	t_image	q;

	q.x_ratio = (double)old_size->x / new_size.x;
	q.y_ratio = (double)old_size->y / new_size.y;
	q.dest = mlx_new_image(mlx, new_size.x, new_size.y);
	if (!q.dest)
		return (NULL);
	q.src_data = (int *)mlx_get_data_addr(img, &q.bps, &q.len, &q.endian);
	q.scl_d = (int *)mlx_get_data_addr(q.dest, &q.bps, &q.len, &q.endian);
	q.pos.y = 0;
	while (q.pos.y < new_size.y)
	{
		q.pos.x = 0;
		while (q.pos.x < new_size.x)
		{
			q.size.x = (int)(q.pos.x * q.x_ratio);
			q.size.y = (int)(q.pos.y * q.y_ratio);
			q.scl_d[q.pos.y * new_size.x + q.pos.x] = \
				q.src_data[q.size.y * old_size->x + q.size.x];
			q.pos.x++;
		}
		q.pos.y++;
	}
	mlx_destroy_image(mlx, img);
	*img = q.dest;
	return (set_vec2(old_size, new_size.x, new_size.y), q.dest);
}

void	*get_image_copy(t_md *mlx_ptr, void *src, t_vec2 src_size)
{
	t_image	img;
	t_vec2	src_pos;
	t_vec2	dst_pos;

	img.dest = mlx_new_image(mlx_ptr, src_size.x, src_size.y);
	if (img.dest == NULL)
		return (NULL);
	img.src_data = (int *)mlx_get_data_addr(src, &img.bpp, &src_pos.x, \
		&img.endian);
	img.dst_data = (int *)mlx_get_data_addr(img.dest, &img.bpp, &dst_pos.x, \
		&img.endian);
	img.pos.y = 0;
	while (img.pos.y < src_size.y)
	{
		img.pos.x = 0;
		while (img.pos.x < src_size.x)
		{
			src_pos.y = (img.pos.y * src_pos.x / 4) + img.pos.x;
			dst_pos.y = (img.pos.y * dst_pos.x / 4) + img.pos.x;
			img.dst_data[dst_pos.y] = img.src_data[src_pos.y];
			img.pos.x++;
		}
		img.pos.y++;
	}
	return (img.dest);
}

void	my_mlx_pixel_put(t_md *data, int x, int y, int color)
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
		ft_printf("ERROR: Failed to load image at path: %s\n", relative_path);
		return (NULL);
	}
	return (img);
}
