/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 05:36:59 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 17:15:43 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

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
			if (md->plr.is_grounded == i && !md->key_prs[W_KEY])
			{
				hurt_entity(md, e, AU_AXE, AU_AXE_BREAK);
				md->plr.movement.y = -100;
			}
			if (!md->coins_amount && move_to_simple(e, md->ext_p, 5))
				e->is_active = 0;
			else if (md->coins_amount)
				update_mob_entity(e, md, &md->plr);
		}
	}
}

void	update_key_entity(t_md *md, t_ent *e, int range, t_vec3 targ_pos)
{
	if (e->hp == 0)
	{
		e->flip_x = md->plr.flip_x;
		targ_pos = get_vec3(md->plr.pos.x, md->plr.pos.y, 0);
		if (!md->key)
			md->key = e;
	}
	else if (e->hp < 0)
	{
		if (md->key_clicked == ENTER_KEY)
		{
			hurt_entity(md, md->images[-e->hp], AU_AXE_BREAK, AU_AXE_BREAK);
			e->is_active = 0;
			if (md->key == e)
				md->key = NULL;
		}
		else if (abs(get_distance(md->plr.pos, md->images[-e->hp]->pos)) \
			>= md->t_len * 2)
			e->hp = 0;
		else
			targ_pos = get_vec3(md->images[-e->hp]->pos.x, \
				md->images[-e->hp]->pos.y + md->t_len / 5, 0);
	}
	if (targ_pos.x != 0 && targ_pos.y != 0)
		move_ent_towards(e, md, targ_pos, range);
}

void	update_door(t_md *md, t_ent *e, int i)
{
	if (!md->key || md->key->type != key)
		return ;
	if (md->key->hp == 0 && \
			abs(get_distance(e->pos, md->plr.pos)) < md->t_len * 2)
		md->key->hp = -i;
}

void	update_env(t_md *md, int i)
{
	t_ent	*e;

	while (md->images[i])
	{
		e = md->images[i];
		if (e->hurt_timer)
			e->hurt_timer--;
		if ((e->type == mob || e->type == wall || e->type == door) \
			&& !e->hp && !e->hurt_timer)
			e->is_active = 0;
		e->prv_pos = e->pos;
		if (e->is_active <= 0)
		{
			i++;
			continue ;
		}
		if (e->is_active)
			update_entity_position(e, md, i);
		if (e->type == door)
			update_door(md, e, i);
		if (md->images[i] == e)
			i++;
	}
}
