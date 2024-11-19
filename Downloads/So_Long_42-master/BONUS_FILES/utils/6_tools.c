/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:21:44 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 17:04:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	r_range(int min, int max)
{
	if (min > max)
		return (-1);
	return (min + rand() % (max - min + 1));
}

int	get_array_size(void **array)
{
	int	count;

	if (!array)
		return (-1);
	count = 0;
	while (array[count])
		count++;
	return (count);
}

// PARAMS: bpp[0] line_length[1] endian[2] src_offset[3] dest_offset[4]
void	*flip_image_x(void *mlx, void *img, t_vec2 size)
{
	t_vec2	pos;
	int		prm[5];
	void	*flipped_img;
	char	*src_data;
	char	*dest_data;

	flipped_img = mlx_new_image(mlx, size.x, size.y);
	if (!flipped_img)
		return (NULL);
	src_data = mlx_get_data_addr(img, &prm[0], &prm[1], &prm[2]);
	dest_data = mlx_get_data_addr(flipped_img, &prm[0], &prm[1], &prm[2]);
	if (!src_data || !dest_data)
		return (NULL);
	pos.y = -1;
	while (++pos.y < size.y)
	{
		pos.x = -1;
		while (++pos.x < size.x)
		{
			prm[3] = pos.y * prm[1] + (size.x - pos.x - 1) * (prm[0] / 8);
			prm[4] = pos.y * prm[1] + pos.x * (prm[0] / 8);
			ft_memcpy(dest_data + prm[4], src_data + prm[3], prm[0] / 8);
		}
	}
	return (flipped_img);
}

int	move_to_simple(t_ent *e, t_vec3 targ_pos, int spd)
{
	t_vec2	dpos;
	float	dist;

	set_vec2(&dpos, targ_pos.x - e->pos.x, targ_pos.y - e->pos.y);
	dist = sqrt(dpos.x * dpos.x + dpos.y * dpos.y);
	if (dist == 0)
		return (1);
	e->pos.x += (int)((dpos.x / dist) * spd);
	e->pos.y += (int)((dpos.y / dist) * spd);
	if (abs(e->pos.x - targ_pos.x) < spd && abs(e->pos.y - targ_pos.y) < spd)
	{
		e->pos.x = targ_pos.x;
		e->pos.y = targ_pos.y;
		return (1);
	}
	return (0);
}
