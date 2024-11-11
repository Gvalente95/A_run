/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_Vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:07:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/11 12:55:25 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

int set_Vec2(t_vec2 *Vec2, int x, int y)
{
    if (!Vec2)
        return (0);
    Vec2->x = x;
    Vec2->y = y;
    return (1);
}

int set_Vec3(t_vec3 *Vec3, int x, int y, int z)
{
    if (!Vec3)
        return (0);
    Vec3->x = x;
    Vec3->y = y;
    Vec3->z = z;
    return (1);
}

t_vec2	get_Vec2(int x, int y)
{
	t_vec2	res;

	res.x = x;
	res.y = y;
	return res;
}

t_vec3	get_Vec3(int x, int y, int z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

char print_Vec3(t_vec3 Vec3)
{
    printf("%d %d %d", Vec3.x, Vec3.y, Vec3.z);
    return ('\n');
}
