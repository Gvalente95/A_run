/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:21:44 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/11 03:41:13 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int rand_range(int min, int max)
{
    if (min > max)
        return -1;
    return min + rand() % (max - min + 1);
}

t_Vec3 rand_Vec3(int min, int max)
{
    t_Vec3 vec;

    set_Vec3(&vec, 0,0,0);
    if (rand() % 2 == 0)
        vec.x = rand_range(min, max);
    else
        vec.y = rand_range(min, max);
    return (vec);
}

char **get_frames_paths(char *path, char *suffix, int amount)
{
    int     i;
    char    *num_value;
    char    **FRAMES_PATH;
    char    *with_suffix;
    char    *with_format;
    char    *format;

	//ft_printf("PATH: %s SUFFIX: %s\n", path, suffix);

    format = strdup(".png");
    FRAMES_PATH = malloc(sizeof(char *) * amount + 1);
    if (!FRAMES_PATH)
        return (NULL);
    i = 0;
    while (i < amount)
    {
        num_value = ft_itoa(i);
		with_suffix = ft_strjoin(suffix, num_value);
        free(num_value);
        with_format = ft_strjoin(with_suffix, format);
        FRAMES_PATH[i] = ft_strjoin(path, with_format);
        //ft_printf("FRAME[%d]: %s\n", i, FRAMES_PATH[i]);
        free(with_format);
        free(with_suffix);
        i++;
    }
	FRAMES_PATH[i] = NULL;
    return (FRAMES_PATH);
}

int get_array_size(void **array)
{
	int count;

	if (!array)
		return (-1);
	count = 0;
	while (array[count])
		count++;
	return (count);	
}

void *flip_image_x(void *mlx, void *img, int width, int height)
{
    int x, y;
    int bpp;
    int line_length;
    int endian;

    void *flipped_img = mlx_new_image(mlx, width, height);
    if (!flipped_img)
        return NULL;
    char *src_data = mlx_get_data_addr(img, &bpp, &line_length, &endian);
    char *dest_data = mlx_get_data_addr(flipped_img, &bpp, &line_length, &endian);
    if (!src_data || !dest_data)
        return NULL;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            int src_offset = y * line_length + (width - x - 1) * (bpp / 8);
            int dest_offset = y * line_length + x * (bpp / 8);
            memcpy(dest_data + dest_offset, src_data + src_offset, bpp / 8);
        }
    }
    return flipped_img;
}