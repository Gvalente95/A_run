/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_particles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:32:40 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 00:51:21 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	reset_particle(t_md *md, t_prt *p)
{
	p->is_active = 0;
	p->movement = get_vec2(0, 0);
	p->lifetime = 0;
	md->particles_alive--;
	return (1);
}

int	activate_particle(t_md *md, t_prt *e, t_vec3 pos, int dur)
{
	t_vec2	dir;

	dir = get_vec2((r_range(0, 1) * 2) - 1, (r_range(0, 1) * 2) - 1);
	e->is_active = 1;
	e->pos = get_vec2(pos.x + dir.x * md->t_len / 2, \
		pos.y + dir.y * md->t_len / 2);
	e->dir = r_range(0, 4);
	e->lifetime = dur + \
		r_range(-(dur / 3), dur / 3);
	e->movement = get_vec2(dir.x * (r_range(1, 3) * e->lifetime), \
		dir.y * r_range(-1, 3) * e->lifetime);
	md->particles_alive++;
	return (1);
}

int	set_particles(t_md *md, int amount, t_vec3 pos, int dur)
{
	int		i;
	int		amount_at_start;

	if (!md->particles || md->particles_alive >= PRT_AMOUNT)
		return (0);
	i = md->particles_alive;
	while (md->particles_alive > PRT_AMOUNT)
	{
		if (md->particles[i]->is_active)
			reset_particle(md, md->particles[i]);
		i--;
	}
	i = 0;
	amount_at_start = md->particles_alive;
	while (md->particles[i] && md->particles_alive - amount_at_start < amount)
	{
		if (!md->particles[i]->is_active)
			activate_particle(md, md->particles[i], pos, dur);
		i++;
	}
	ft_printf("PRT_ACTIVE: %d\nPARTICLES ACTIVATED %d\n", md->particles_alive, \
		md->particles_alive - amount_at_start);
	return (md->particles_alive - amount_at_start);
}

int	update_particle(t_md *md, t_prt *e)
{
	if (!e->is_grounded)
		e->movement.y += 3;
	handle_movement(md, (t_ent)e, get_vec2(2, 2), get_vec2(0, 0));
	if (e->lifetime && md->time % 5 == 0)
		e->lifetime--;
	if (e->lifetime <= 0 || (e->movement.x == 0 && e->movement.y == 0))
	{
		reset_particle(md, e);
		return (0);
	}
	return (1);
}

void	update_particles(t_md *md)
{
	int		i;
	int		live_amount;

	live_amount = 0;
	i = 0;
	while (i < md->particles_alive && i < PRT_AMOUNT)
	{
		if (!md->particles[i]->is_active)
		{
			i++;
			continue ;
		}
		live_amount += update_particle(md, md->particles[i]);
		i++;
	}
	if (!live_amount)
		md->particles_alive = 0;
}
