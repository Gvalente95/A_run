/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_entity_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:32:45 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 18:06:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	get_distance(t_vec3 a, t_vec3 b)
{
	return ((int)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
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
		set_particles(md, r_range(30, 35), e->pos, splat);
		e->hurt_timer = 30;
	}
	else
	{
		play_random_sound(hit_path, 6, ".mp3");
		set_particles(md, r_range(3, 6), e->pos, splat);
		e->hurt_timer = 10;
	}
	return (e->hp);
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
