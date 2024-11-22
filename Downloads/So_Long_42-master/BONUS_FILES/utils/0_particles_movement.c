/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_particles_movement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:10:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 22:32:52 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_ent	copy_prt_to_ent(t_prt *p)
{
	t_ent	e;

	e.is_active = 1;
	e.is_grounded = p->is_grounded;
	e.pos = get_vec3(p->pos.x, p->pos.y, 0);
	e.dir = p->dir;
	e.movement = get_vec3(p->movement.x, p->movement.y, 0);
	e.hp = p->lifetime;
	e.size = p->size;
	e.type = particle;
	e.prt_type = p->type;
	e.frames_amount = 0;
	e.cur_frame = NULL;
	return (e);
}

void	copy_ent_to_prt(t_prt *p, t_ent e)
{
	p->is_grounded = e.is_grounded;
	p->pos = get_vec2(e.pos.x, e.pos.y);
	p->dir = e.dir;
	p->lifetime = e.hp;
	p->movement = get_vec2(e.movement.x, e.movement.y);
}

int	handle_prt_movement(t_md *md, t_prt *p, t_vec2 cols)
{
	t_ent	e;

	(void)cols;
	e = copy_prt_to_ent(p);
	if (p->type == trail)
	{
		move_ent_towards(&e, md, md->plr.prv_pos, 200);
	}
	cols = handle_movement(md, &e, get_vec2(1, 1), get_vec2(1, 1));
	copy_ent_to_prt(p, e);
	return (1);
}

t_vec2	set_prt_movement(t_vec3 pos, t_vec3 target, t_prt *prt)
{
	float	dx;
	float	dy;
	float	magnitude;

	dx = target.x - pos.x;
	dy = target.y - pos.y;
	magnitude = sqrt(dx * dx + dy * dy);
	if (magnitude != 0)
	{
		dx = (dx / magnitude) * 120;
		dy = (dy / magnitude) * 150;
	}
	prt->movement = get_vec2(dx, dy);
	return (prt->movement);
}
