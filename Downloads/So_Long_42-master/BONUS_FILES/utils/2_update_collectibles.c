/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_collectibles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:11:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 16:31:22 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	set_target_position(t_vec3 *p, t_vec2 *target_size, \
	t_md *md, t_ent *target)
{
	if (!md->coins_amount)
	{
		set_vec3(p, md->ext_p.x + r_range(-3, 3), md->ext_p.y + \
			r_range(-4, 4), 0);
		*target_size = md->exit->size;
	}
	else
	{
		*p = target->pos;
		*target_size = target->size;
	}
}

void	update_coin_entity(t_ent *e, t_md *md, int range, int index)
{
	t_vec3	p;
	t_vec2	target_size;

	(void)index;
	set_target_position(&p, &target_size, md, &md->plr);
	if (!e->hp)
		range = 9000;
	if (!md->coins_amount && destroy_if_reached(e, md, target_size, p))
	{
		play_sound(md->coin_paths[r_range(0, 4)], 0);
		return ;
	}
	update_circular_motion(e, md);
	if (move_ent_towards(e, md, p, range))
	{
		play_sound(md->coin_paths[r_range(0, 4)], 0);
		md->coins_amount--;
		e->hp--;
	}
}

t_ent	*hit_block(t_md *md)
{
	t_ent	*block;
	t_vec3	mouse_pos;

	mouse_pos = get_vec3(md->mouse_pos[0], md->mouse_pos[1], 0);
	block = get_ent_at_pos(mouse_pos, get_vec2(1, 1), md->images, wall);
	if (block && get_distance(*block, md->plr) < (md->t_len * 2) - 1)
	{
		block->hp--;
		if (block->hp == 0)
			play_random_sound(AU_AXE_BREAK, 3, ".wav");
		else
			play_random_sound(AU_AXE, 6, ".wav");
		block->hurt_timer = 10;
	}
	return (block);
}

void	update_axe_entity(t_ent *e, t_md *md, int range)
{
	t_vec3	p;

	if (!e->hp)
		range = 900;
	if (!(md->mouse_pressed == MOUSE_PRESS && !e->hp))
		p = md->plr.pos;
	if (md->plr.flip_x)
		set_vec3(&p, p.x + 30, p.y + 30, 0);
	else
		set_vec3(&p, p.x - 60, p.y + 30, 0);
	if (!e->hp)
	{
		if (md->mouse_pressed == MOUSE_PRESS)
			set_ent_to_mouse(e, md);
		if (md->mouse_clicked == MOUSE_PRESS)
			hit_block(md);
	}
	if (move_ent_towards(e, md, p, range))
	{
		play_random_sound(AU_AXE, 4, ".wav");
		e->hp--;
	}
}

void	update_collectible(t_ent *e, t_md *md, int range, int index)
{
	update_circular_motion(e, md);
	if (md->time % ANIM_REFRESH == 0)
		increment_frame(e);
	if (e->type == coin)
		update_coin_entity(e, md, range, index);
	if (e->type == axe)
		update_axe_entity(e, md, 80);
	if (e->type == key)
	{
		if (!e->hp)
		{
			e->flip_x = md->plr.flip_x;
			if (md->plr.flip_x)
				set_vec3(&e->pos, md->plr.pos.x - md->plr.size.x, \
					md->plr.pos.y + 30, e->pos.z);
			else
				set_vec3(&e->pos, md->plr.pos.x + 70, md->plr.pos.y + 30, 0);
		}
		if (move_ent_towards(e, md, md->plr.pos, range))
		{
			play_random_sound(AU_AXE, 4, ".wav");
			e->hp = 0;
		}
	}
}
