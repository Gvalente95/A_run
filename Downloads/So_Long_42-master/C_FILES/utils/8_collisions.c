/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_collisions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:38:21 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 16:48:57 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	handle_col(t_ent *e, int *col_dir)
{
	int	displ_am;

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

t_vec2	calculate_displacement(t_ent *a, t_ent *b, t_vec2 displ)
{
	t_vec2	displacement;
	int		dlt_l;
	int		dlt_r;
	int		dlt_up;
	int		dlt_down;

	set_vec2(&displacement, 0, 0);
	dlt_l = (a->pos.x + a->size.x) - b->pos.x;
	dlt_r = (b->pos.x + b->size.x) - a->pos.x;
	dlt_up = (a->pos.y + a->size.y) - b->pos.y;
	dlt_down = (b->pos.y + b->size.y) - a->pos.y;
	if (dlt_up < dlt_down && dlt_up < dlt_l && dlt_up < dlt_r)
		displacement.y = -dlt_up + displ.y;
	else if (dlt_down < dlt_up && dlt_down < dlt_l && dlt_down < dlt_r)
		displacement.y = dlt_down - displ.y;
	else if (dlt_l < dlt_r && dlt_l < dlt_up && dlt_l < dlt_down)
		displacement.x = -dlt_l + displ.x;
	else if (dlt_r < dlt_up && dlt_r < dlt_down)
		displacement.x = dlt_r - displ.x;
	return (displacement);
}

t_vec2	get_collision_displacement(t_ent *e1, t_ent *e2, \
	int e2_index, t_vec2 displ)
{
	t_vec2	displacement;
	int		is_same_x;
	int		is_same_y;

	set_vec2(&displacement, 0, 0);
	is_same_x = e1->pos.x + displ.x < e2->pos.x + \
		e2->size.x && e1->pos.x + e1->size.x - displ.x > e2->pos.x;
	is_same_y = e1->pos.y + displ.y < e2->pos.y + e2->size.y && \
		e1->pos.y + e1->size.y - displ.y > e2->pos.y;
	if (is_same_x && is_same_y)
		displacement = calculate_displacement(e1, e2, displ);
	if (displacement.y == 0 && is_same_x && abs((e1->pos.y + displ.y + \
		e1->size.y) - e2->pos.y + displ.y) <= 1)
	{
		e1->is_grounded = e2_index;
		if (!e1->jump_timer && !e1->jet_sky_timer)
			e1->pos.y = e2->pos.y - e1->size.y;
	}
	else if (displacement.y < 0)
		e1->is_grounded = 1;
	return (displacement);
}

t_vec2	get_collisions(t_ent *e, t_ent **col_ents, t_vec2 displ)
{
	t_vec2	collisions;
	t_vec2	displacement;
	int		i;

	set_vec2(&collisions, 0, 0);
	if (!col_ents)
		return (collisions);
	e->is_grounded = 0;
	i = -1;
	while (col_ents[++i] != NULL)
	{
		if (col_ents[i] == e || !col_ents[i]->is_active)
			continue ;
		if ((e->type == coin && col_ents[i]->type != coin) || \
		(col_ents[i]->type != wall && col_ents[i]->type != tile && \
		col_ents[i]->type != mob))
			continue ;
		displacement = get_collision_displacement(e, col_ents[i], i, displ);
		collisions.x += displacement.x;
		collisions.y += displacement.y;
	}
	return (collisions);
}

t_ent	*get_ent_simple(t_vec2 pos, t_ent **ents)
{
	int	i;

	i = 0;
	while (ents[i])
	{
		if (ents[i]->is_active && ents[i]->pos.x == pos.x && \
			ents[i]->pos.y == pos.y)
			return (ents[i]);
		i++;
	}
	return (NULL);
}
