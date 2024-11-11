/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_collisions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:47:08 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/11 06:43:33 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

#include <math.h>  // For sqrt

int move_towards(t_ent *e, t_Vec3 target_pos, int min_speed, int max_speed, int aggro_range)
{
    int dx = target_pos.x - e->pos.x;
    int dy = target_pos.y - e->pos.y;
    float distance = sqrt(dx * dx + dy * dy);
    if (distance > aggro_range)
        return 0;
    if (distance == 0)
        return 1;
    int speed = (int)(min_speed + (max_speed - min_speed) * (1 - distance / aggro_range));
    float direction_x = (float)dx / distance;
    float direction_y = (float)dy / distance;
    e->pos.x += (int)(direction_x * speed);
    e->base_pos.y += (int)(direction_y * speed);
    if (abs(e->pos.x - target_pos.x) < speed && abs(e->pos.y - target_pos.y) < speed)
    {
        e->pos.x = target_pos.x;
        e->base_pos.y = target_pos.y;
        return 1;
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

t_Vec2 get_collision_displacement(t_ent *entity1, t_ent *entity2, int entity2_index)
{
    t_Vec2 displacement = {0, 0};
	int is_same_x;
	int is_same_y;

	is_same_x = entity1->pos.x < entity2->pos.x + entity2->size.x &&
        entity1->pos.x + entity1->size.x > entity2->pos.x;
	is_same_y = entity1->pos.y < entity2->pos.y + entity2->size.y &&
        entity1->pos.y + entity1->size.y > entity2->pos.y;
    if (is_same_x && is_same_y)
    {
        int delta_left = (entity1->pos.x + entity1->size.x) - entity2->pos.x;
        int delta_right = (entity2->pos.x + entity2->size.x) - entity1->pos.x;
        int delta_top = (entity1->pos.y + entity1->size.y) - entity2->pos.y;
        int delta_bottom = (entity2->pos.y + entity2->size.y) - entity1->pos.y;
        if (delta_top < delta_bottom && delta_top < delta_left && delta_top < delta_right)
            displacement.y = -delta_top;
        else if (delta_bottom < delta_top && delta_bottom < delta_left && delta_bottom < delta_right)
            displacement.y = delta_bottom;
        else if (delta_left < delta_right && delta_left < delta_top && delta_left < delta_bottom)
            displacement.x = -delta_left;
        else if (delta_right < delta_top && delta_right < delta_bottom)
            displacement.x = delta_right;
    }
	int ground_margin = 5;

    if (displacement.y == 0 && is_same_x && abs((entity1->pos.y + entity1->size.y) - entity2->pos.y) <= ground_margin)
	{
		entity1->is_grounded = entity2_index;
		if (!entity1->jump_timer && !entity1->jet_sky_timer)
			entity1->pos.y = entity2->pos.y - entity1->size.y;
	}
	else if (displacement.y < 0)
		entity1->is_grounded = 1;

    return displacement;
}

t_Vec2 get_collisions(t_ent *e, t_ent **col_ents)
{
    t_Vec2 collisions = {0, 0}; // Initialize to zero
    t_Vec2 displacement;
    int i;

	if (!col_ents)
		return (collisions);
	e->is_grounded = 0;
	i = -1;
    while (col_ents[++i] != NULL)
    {
        if (col_ents[i] == e || col_ents[i]->pos.z > e->pos.z)
            continue;
		if (col_ents[i]->type != wall && col_ents[i]->type != tile)
			continue;
        displacement = get_collision_displacement(e, col_ents[i], i);
        collisions.x += displacement.x;
        collisions.y += displacement.y;
    }
    return collisions;
}

int is_in_pos(t_Vec3 pos1, t_Vec2 size1, t_Vec3 pos2, t_Vec2 size2)
{
	return (pos1.x < pos2.x + size2.x &&
        pos1.x + size1.x > pos2.x && pos1.y < pos2.y + size2.y &&
        pos1.y + size1.y > pos2.y);
}

t_ent **get_ents_at_pos(t_Vec3 pos, t_Vec2 size, t_ent **ents, int ents_len)
{
	t_ent **e;
	int len;
	int i;

	i = -1;
	len = 0;
	e = malloc(sizeof(t_ent *) * (ents_len + 1));
	if (!e)
		return (NULL);
	while (ents[++i] != NULL && i < ents_len)
	{
		if (is_in_pos(pos, size, ents[i]->pos, ents[i]->size))
			e[len++] = ents[i];
	}
	e[len] = NULL;
	return (e);
}

int delete_at_index(int index, t_ent **ents, int len)
{
    if (!ents[index])
        return len;
    free(ents[index]);
    ents[index] = NULL;
    while (index < len - 1)
    {
        ents[index] = ents[index + 1];
        index++;
    }
    ents[len - 1] = NULL;
    return --len;
}

int delete_ents_at_pos(t_Vec3 pos, t_Vec2 size, t_ent **ents, int *ents_len)
{
    int i;
	int deleted_amount;

	deleted_amount = 0;
	i = -1;
	if (*ents_len == 1 && is_in_pos(pos, size, ents[0]->pos, ents[0]->size))
	{
		free(ents[0]);
		ents[0] = NULL;
		*ents_len = 0;
		return (1);
	}
	else while (++i < *ents_len)
	{
		if (ents[i] != NULL && is_in_pos(pos, size, ents[i]->pos, ents[i]->size))
			*ents_len = delete_at_index(i, ents, *ents_len);
	}
    return deleted_amount;
}

int delete_type(t_ent_type type, t_ent **ents, int *ents_len)
{
    int i;
	int deleted_amount;

	deleted_amount = 0;
	i = -1;
	while (++i < *ents_len)
	{
		if (ents[i] != NULL && ents[i]->type == type)
			*ents_len = delete_at_index(i, ents, *ents_len);
	}
    return deleted_amount;
}


t_ent *get_at_pos(t_Vec3 pos, t_Vec2 size, t_ent **ents, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (ents[i] != NULL && is_in_pos(pos, size, ents[i]->pos, ents[i]->size))
			return (ents[i]);
	}
	return (NULL);
}