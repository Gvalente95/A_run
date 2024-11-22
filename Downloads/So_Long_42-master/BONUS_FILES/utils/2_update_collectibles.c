/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_collectibles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:11:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 00:40:02 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

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

void	update_coin_entity(t_ent *e, t_md *md, int range)
{
	t_vec3	p;
	t_vec2	target_size;

	set_target_position(&p, &target_size, md, &md->plr);
	if (!e->hp)
		range = 9000;
	update_circular_motion(e, md);
	if (move_ent_towards(e, md, p, range) && e->hp)
	{
		if (md->coins_amount == 1)
			play_sound(AU_LEVELUP, 0);
		md->coins_amount--;
		e->hp--;
		if (!md->coin_au_timer)
		{
			play_random_sound(AU_COINS, 4, ".mp3");
			md->coin_au_timer = 10;
		}
	}
}

t_ent	*hit_block(t_md *md)
{
	t_ent	*blk;

	blk = get_ent_at_pos(md->mouse_pos, get_vec2(1, 1), md->images, wall);
	if (blk && blk->hp && get_distance(blk->pos, md->plr.pos) < \
		(md->t_len * 2) - 1)
		hurt_entity(md, blk, AU_AXE, AU_AXE_BREAK);
	return (blk);
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
		play_random_sound(AU_AXE, 4, ".mp3");
		e->hp--;
	}
}

void	update_collectible(t_ent *e, t_md *md, int range, int index)
{
	t_vec3	targ_pos;

	(void)index;
	update_circular_motion(e, md);
	if (md->time % ANIM_REFRESH == 0)
		increment_frame(e);
	if (e->type == coin)
		update_coin_entity(e, md, md->t_len * 2);
	if (e->type == axe)
		update_axe_entity(e, md, md->t_len * 2);
	if (e->type == key)
	{
		if (e->hp > 0 && move_ent_towards(e, md, md->plr.pos, range))
		{
			play_random_sound(AU_AXE, 4, ".mp3");
			md->key = e;
			e->hp = 0;
		}
		else
		{
			targ_pos = update_key_entity(md, e, get_vec3(0, 0, 0));
			if (targ_pos.x != 0 && targ_pos.y != 0)
				move_ent_towards(e, md, targ_pos, range);
		}
	}
}
