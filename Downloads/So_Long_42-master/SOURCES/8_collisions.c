/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_collisions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:47:08 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 16:59:53 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_dir is_colliding(t_ent *entity1, t_ent *entity2)
{
    if (entity1->pos.x < entity2->pos.x + entity2->size.x &&
        entity1->pos.x + entity1->size.x > entity2->pos.x &&
        entity1->pos.y < entity2->pos.y + entity2->size.y &&
        entity1->pos.y + entity1->size.y > entity2->pos.y)
    {
        int delta_left = (entity1->pos.x + entity1->size.x) - entity2->pos.x;
        int delta_right = (entity2->pos.x + entity2->size.x) - entity1->pos.x;
        int delta_top = (entity1->pos.y + entity1->size.y) - entity2->pos.y;
        int delta_bottom = (entity2->pos.y + entity2->size.y) - entity1->pos.y;

        if (delta_top < delta_bottom && delta_top < delta_left && delta_top < delta_right)
            return down;
        else if (delta_bottom < delta_top && delta_bottom < delta_left && delta_bottom < delta_right)
            return up;
        else if (delta_left < delta_right - 10 && delta_left < delta_top && delta_left < delta_bottom - 10)
            return left;
        else if (delta_right < delta_top - 10 && delta_right < delta_bottom - 10)
            return right;
    }
    return none;
}

int is_ent_colliding(t_mlx_data *mlx_data, t_ent *e)
{
    t_ent *env;
    int i;

    i = -1;
    while (++i < ENV_AMOUNT)
    {
        env = &mlx_data->env[i];
        if (env == e)
            continue;
        if (is_colliding(e, env) != none)
            return (1);
    }
    return 0;
}

void	handle_col(t_ent *e, int *col_dir)
{
	int displ_am;

	displ_am = 10;
	if (col_dir[up])
		e->pos.y -= displ_am;
	else if (col_dir[down])
		e->pos.y += displ_am;
	else if (col_dir[left])
		e->pos.x -= displ_am;
	else if (col_dir[right])
		e->pos.x += displ_am;
	if (col_dir[up] || col_dir[down])
		e->movement.y = 0;
	if (col_dir[left] || col_dir[right])
		e->movement.x = 0;
}


t_Vec2 get_collision_displacement(t_ent *entity1, t_ent *entity2)
{
    t_Vec2 displacement = {0, 0};

    if (entity1->pos.x < entity2->pos.x + entity2->size.x &&
        entity1->pos.x + entity1->size.x > entity2->pos.x &&
        entity1->pos.y < entity2->pos.y + entity2->size.y &&
        entity1->pos.y + entity1->size.y > entity2->pos.y)
    {
        int delta_left = (entity1->pos.x + entity1->size.x) - entity2->pos.x;
        int delta_right = (entity2->pos.x + entity2->size.x) - entity1->pos.x;
        int delta_top = (entity1->pos.y + entity1->size.y) - entity2->pos.y;
        int delta_bottom = (entity2->pos.y + entity2->size.y) - entity1->pos.y;
		if (delta_top <= delta_bottom - 1 && delta_top < delta_left && delta_top < delta_right)
			entity1->is_grounded = 1;

        if (delta_top < delta_bottom && delta_top < delta_left && delta_top < delta_right)
            displacement.y = -delta_top;
        else if (delta_bottom < delta_top && delta_bottom < delta_left && delta_bottom < delta_right)
            displacement.y = delta_bottom;
        else if (delta_left < delta_right && delta_left < delta_top && delta_left < delta_bottom)
            displacement.x = -delta_left;
        else if (delta_right < delta_top && delta_right < delta_bottom)
            displacement.x = delta_right;
    }
    return displacement;
}

t_Vec2 get_collisions(t_ent *e, t_mlx_data *mlx_data)
{
    t_Vec2 collisions = {0, 0}; // Initialize to zero
    t_Vec2 displacement;
    int i;
	e->is_grounded = 0;

    for (i = 0; i < ENV_AMOUNT; i++)
    {
        if (&mlx_data->env[i] == e) // Skip self-collision
            continue;
        displacement = get_collision_displacement(e, &mlx_data->env[i]);
        // Accumulate displacement if a collision is detected
        collisions.x += displacement.x;
        collisions.y += displacement.y;
    }
    return collisions;
}
