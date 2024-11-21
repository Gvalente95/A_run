/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_particles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:32:40 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 21:29:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	reset_particle(t_md *md, t_prt *p, int index)
{
	t_prt	*temp;

	p->is_active = 0;
	p->movement = get_vec2(0, 0);
	p->pos = get_vec2(0, 0);
	p->lifetime = 0;
	md->particles_alive--;
	while (index < md->particles_alive && index < PRT_AMOUNT - 1)
	{
		if (md->particles[index + 1]->is_active)
		{
			temp = md->particles[index];
			md->particles[index] = md->particles[index + 1];
			md->particles[index + 1] = temp;
		}
		index++;
	}
	return (1);
}

int	activate_particle(t_md *md, t_prt *p, t_vec3 pos, t_prt_type type)
{
	t_vec2	dir;

	p->is_active = 1;
	p->movement = get_vec2(0, 0);
	p->pos = get_vec2(0, 0);
	dir = get_vec2((r_range(0, 1) * 2) - 1, (r_range(0, 1) * 2) - 1);
	p->type = type;
	p->pos = get_vec2(pos.x + dir.x * md->t_len / 2, \
		pos.y + dir.y * md->t_len / 2);
	if (p->type == target)
		p->pos = get_vec2(pos.x + r_range(-5, 5), pos.y + r_range(-5, 5));
	p->dir = r_range(0, 4);
	p->lifetime = 60;
	p->foll_ofs = get_vec2(r_range(-5, 5), r_range(-5, 5));
	if (type == splat)
	{
		p->lifetime = 100 + r_range(-(100 / 3), 100 / 3);
		p->movement = get_vec2(dir.x * (r_range(1, 3) * (p->lifetime / 10)), \
			dir.y * r_range(-1, 3) * (p->lifetime / 10));
	}
	else if (type == target || type == trail)
		set_prt_movement(pos, md->mouse_pos, p);
	md->particles_alive++;
	return (1);
}

int	set_particles(t_md *md, int amount, t_vec3 pos, t_prt_type type)
{
	int		i;
	int		amount_at_start;

	if (!md->particles)
		return (0);
	i = 0;
	while (md->particles_alive > PRT_AMOUNT && i < md->particles_alive)
	{
		if (md->particles[i]->is_active)
			reset_particle(md, md->particles[i], i);
		i++;
	}
	i = 0;
	amount_at_start = md->particles_alive;
	while (i < PRT_AMOUNT && md->particles_alive - amount_at_start < amount)
	{
		if (!md->particles[i]->is_active)
		{
			activate_particle(md, md->particles[i], pos, type);
			md->particles_alive++;
		}
		i++;
	}
	return (md->particles_alive - amount_at_start);
}

int	update_particle(t_md *md, t_prt *p, int index)
{
	if (!p->is_grounded)
		p->movement.y += 3;
	handle_prt_movement(md, p, get_vec2(0, 0));
	if (p->lifetime && md->time % 5 == 0)
		p->lifetime--;
	if (p->lifetime <= 0)
	{
		reset_particle(md, p, index);
		return (0);
	}
	return (1);
}

void	update_particles(t_md *md)
{
	int		i;

	if (md->key_clicked == ENTER_KEY)
	{
		set_particles(md, 10, get_vec3(md->plr.pos.x + md->t_len / 2, \
			md->plr.pos.y + md->t_len / 2, 0), target);
		play_random_sound(AU_PARTICLES, 1, ".mp3");
	}
	i = 0;
	while (i < md->particles_alive && i < PRT_AMOUNT)
	{
		if (!md->particles[i]->is_active)
		{
			reset_particle(md, md->particles[i], i);
			continue ;
		}
		if (!update_particle(md, md->particles[i], i))
			continue ;
		i++;
	}
}
