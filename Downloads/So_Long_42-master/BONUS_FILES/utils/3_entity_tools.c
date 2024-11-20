/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_entity_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:32:45 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 00:37:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	get_distance(t_ent a, t_ent b)
{
	return ((int)sqrt(pow(a.pos.x - b.pos.x, 2) + pow(a.pos.y - b.pos.y, 2)));
}

int	destroy_if_reached(t_ent *e, t_md *md, t_vec2 targ_size, t_vec3 p)
{
	(void)md;
	if (is_in_pos(e->pos, e->size, p, targ_size))
	{
		e->is_active = 0;
		return (1);
	}
	return (0);
}

void	update_circular_motion(t_ent *e, t_md *md)
{
	e->pos.y = e->base_pos.y + 5.0 * sin((md->time + e->foll_ofs.x) * .04);
}

int	move_ent_towards(t_ent *e, t_md *md, t_vec3 p, int range)
{
	if (move_to(e, get_vec3(p.x + (md->t_len / 2) - e->foll_ofs.x, p.y - \
e->foll_ofs.y - 3, 0), get_vec2(e->foll_spd - 3, e->foll_spd), range) && e->hp)
		return (1);
	return (0);
}

int	hurt_entity(t_md *md, t_ent *e, char *hit_path, char *kill_path)
{
	e->hp--;
	if (e->hp == 0)
	{
		play_random_sound(kill_path, 3, ".mp3");
		set_particles(md, r_range(30, 35), e->pos, 20);
		e->hurt_timer = 30;
	}
	else
	{
		play_random_sound(hit_path, 6, ".mp3");
		set_particles(md, r_range(3, 6), e->pos, 20);
		e->hurt_timer = 10;
	}
	return (e->hp);
}
