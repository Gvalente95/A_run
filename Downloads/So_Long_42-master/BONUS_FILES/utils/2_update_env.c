/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 05:36:59 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 00:27:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	increment_frame(t_ent *e)
{
	e->cur_frame_index++;
	if (e->cur_frame_index > e->frames_amount - 1 || \
		!e->anim_frames[e->cur_frame_index])
		e->cur_frame_index = 0;
	e->cur_frame = e->anim_frames[e->cur_frame_index];
}

void	update_mob_entity(t_ent *e, t_md *md, t_ent *plr)
{
	if (is_in_pos(e->pos, e->size, plr->pos, plr->size) && \
		plr->is_grounded && !plr->hurt_timer && plr->movement.y == 0)
	{
		hurt_entity(md, &md->plr, AU_HURT, AU_HURT);
		plr->hurt_timer = 200;
		usleep(150000);
	}
	if (!e->is_grounded)
	{
		e->movement.y += 5;
		handle_movement(md, e, get_vec2(1, 1), get_vec2(2, 2));
	}
	else if (!(move_to(e, get_vec3(plr->prv_pos.x + (plr->size.x / 2) - \
e->foll_ofs.x, plr->prv_pos.y - e->foll_ofs.y - 3, 0), get_vec2(1, 3), 200)))
	{
		if (rand() % 100 == 0)
			e->dir = (r_range(0, 1) * 2) + 1;
		set_vec_to_dir(e->dir, &e->movement, 20);
		handle_movement(md, e, get_vec2(50, 50), get_vec2(3, 3));
	}
	if ((e->prv_pos.x != e->pos.x || e->prv_pos.y != e->pos.y) \
		&& md->time % 5 == 0)
		increment_frame(e);
}

void	update_entity_position(t_ent *e, t_md *md, int i)
{
	if (e->type == coin || e->type == key || e->type == axe || \
		e->type == portal)
		update_collectible(e, md, 200, i);
	else
	{
		if (e->type == mob)
		{
			if (!md->coins_amount && move_to_simple(e, md->ext_p, 5))
				e->is_active = 0;
			else if (md->coins_amount)
				update_mob_entity(e, md, &md->plr);
		}
	}
}

void	update_env(t_md *md)
{
	t_ent	*e;
	int		i;

	i = 0;
	while (md->images[i])
	{
		e = md->images[i];
		if (e->hurt_timer)
			e->hurt_timer--;
		if ((e->type == mob || e->type == wall) && !e->hp && !e->hurt_timer)
			e->is_active = 0;
		e->prv_pos = e->pos;
		if (e->type == mob && md->plr.is_grounded == i && !md->key_prs[W_KEY])
		{
			hurt_entity(md, e, AU_AXE, AU_AXE_BREAK);
			md->plr.movement.y = -100;
		}
		if (!e->is_active)
		{
			i++;
			continue ;
		}
		update_entity_position(e, md, i);
		if (md->images[i] == e)
			i++;
	}
}
