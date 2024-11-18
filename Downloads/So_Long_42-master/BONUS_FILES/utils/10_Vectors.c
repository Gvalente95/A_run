/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_Vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:07:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/15 19:26:10 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

int	set_vec2(t_vec2 *Vec2, int x, int y)
{
	if (!Vec2)
		return (0);
	Vec2->x = x;
	Vec2->y = y;
	return (1);
}

int	set_vec3(t_vec3 *Vec3, int x, int y, int z)
{
	if (!Vec3)
		return (0);
	Vec3->x = x;
	Vec3->y = y;
	Vec3->z = z;
	return (1);
}

t_vec2	get_vec2(int x, int y)
{
	t_vec2	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vec3	get_vec3(int x, int y, int z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

void	set_vec_to_dir(t_dir dir, t_vec3 *vec, int mv_am)
{
	if (dir == up)
		vec->y = -mv_am;
	if (dir == down)
		vec->y = mv_am;
	if (dir == left)
		vec->x = -mv_am;
	if (dir == right)
		vec->x = mv_am;
}
