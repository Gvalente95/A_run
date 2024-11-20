/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:58:33 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/20 22:52:53 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	is_in_pos(t_vec3 pos1, t_vec2 size1, t_vec3 pos2, t_vec2 size2)
{
	return (pos1.x < pos2.x + size2.x && \
		pos1.x + size1.x > pos2.x && pos1.y < pos2.y + size2.y && \
		pos1.y + size1.y > pos2.y);
}

void	adjust_x_movement(t_ent *e, int base_speed_x)
{
	int	adjusted_speed;

	adjusted_speed = base_speed_x * (abs(e->movement.x) / \
		(float)(base_speed_x * 14));
	if (e->movement.x > 0)
	{
		e->movement.x--;
		e->pos.x += adjusted_speed;
	}
	else if (e->movement.x < 0)
	{
		e->movement.x++;
		e->pos.x -= adjusted_speed;
	}
}

void	adjust_y_movement(t_ent *e, int base_speed_y)
{
	int	adjusted_speed;

	adjusted_speed = base_speed_y * (abs(e->movement.y) / \
		(float)(base_speed_y * 20));
	if (e->movement.y > 0)
	{
		e->movement.y--;
		e->pos.y += adjusted_speed;
	}
	else if (e->movement.y < 0)
	{
		e->movement.y++;
		e->pos.y -= adjusted_speed;
	}
}

int	handle_movement(t_md *md, t_ent *e, t_vec2 base_speed, t_vec2 displ)
{
	t_vec2	col_dir;

	if (e->type == particle)
		col_dir = get_vec2(0, 0);
	else
	{
		col_dir = get_collisions(md, e, md->images, displ);
		if (col_dir.x != 0)
			e->pos.x += col_dir.x;
		if (col_dir.y != 0)
			e->pos.y += col_dir.y;
	}
	if (e->movement.x != 0)
		adjust_x_movement(e, base_speed.x);
	if (e->movement.y != 0)
		adjust_y_movement(e, base_speed.y);
	if (abs(col_dir.x) > 10)
		return (1);
	return (0);
}

int	move_to(t_ent *e, t_vec3 targ_pos, t_vec2 spd_lim, int aggro)
{
	t_vec2	dpos;
	float	dist;
	int		spd;

	set_vec2(&dpos, targ_pos.x - e->pos.x, targ_pos.y - e->pos.y);
	dist = sqrt(dpos.x * dpos.x + dpos.y * dpos.y);
	spd = (int)(spd_lim.x + (spd_lim.y - spd_lim.x) * (1 - dist / aggro));
	if (dist > aggro)
		return (0);
	if (dist == 0)
		return (1);
	e->pos.x += (int)((float)dpos.x / dist * spd);
	e->base_pos.y += (int)((float)dpos.y / dist * spd);
	if (abs(e->pos.x - targ_pos.x) < spd && abs(e->pos.y - targ_pos.y) < spd)
	{
		e->pos.x = targ_pos.x;
		e->base_pos.y = targ_pos.y;
		return (1);
	}
	return (0);
}
