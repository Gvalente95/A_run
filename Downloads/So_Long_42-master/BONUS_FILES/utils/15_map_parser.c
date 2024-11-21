/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:21:27 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 16:20:38 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

// VALUES: scale | type | z pos
t_ent	*parse_letter_b(t_md *md, t_vec3 pos, char c, int scale)
{
	t_ent	*ent;

	ent = NULL;
	if (c == 'C')
	{
		ent = init_entity(md, COIN_SPR_PATH, get_vec3(pos.x, pos.y, 1), \
	get_vec3(md->t_len / 2 - r_range(md->t_len / 5, md->t_len / 3), coin, 13));
		md->coins_amount++;
	}
	else if (c == 'M')
		ent = init_entity(md, MOB_SPR_PATH, pos, get_vec3(scale * .8, mob, 8));
	else if (c == 'P')
		init_player(md, PLAYER_SPR_PATH, pos);
	else if (c == 'K')
	{
		ent = init_entity(md, KEY_SPR_PATH, pos, get_vec3(scale * .5, key, 8));
		md->key = ent;
	}
	else if (c == 'A')
	{
		ent = init_entity(md, AXE_SPR_PATH, pos, get_vec3(scale * .5, axe, 1));
		md->pickaxe = ent;
	}
	return (ent);
}

t_ent	*parse_letter(t_md *md, t_vec3 pos, char c, int scale)
{
	t_ent	*ent;

	ent = NULL;
	if (c == '1')
		ent = init_entity(md, WALL_SPR_PATH, get_vec3(pos.x, pos.y, 20), \
			get_vec3(scale, wall, 6));
	else if (c == 'E')
	{
		ent = init_entity(md, PORTAL_SPR_PATH, \
			get_vec3(pos.x, pos.y, 2), get_vec3(scale * 2, portal, 9));
		md->exit = ent;
		set_vec3(&md->ext_p, ent->pos.x + (ent->size.x / 3), \
			ent->pos.y + ent->size.y / 2, 0);
	}
	else if (c == 'T')
		ent = init_entity(md, TILES_SPR_PATH, pos, \
			get_vec3(scale / 2, tile, 11));
	else if (c == 'D')
		ent = init_entity(md, DOOR_SPR_PATH, pos, \
			get_vec3(scale, door, 1));
	if (ent)
		return (ent);
	return (parse_letter_b(md, pos, c, scale));
}

void	load_ents(t_md *md, int i, t_vec3 pos)
{
	t_ent	*e;
	int		len;

	len = (md->map.size.x) * (md->map.size.y) + 1;
	md->images = malloc(sizeof(t_ent *) * len);
	i = 0;
	pos.y = 0;
	while (pos.y < md->map.size.y)
	{
		pos.x = 0;
		while (pos.x < md->map.size.x)
		{
			e = parse_letter(md, pos, md->map.buffer[i], md->t_len);
			if (e)
			{
				md->images[md->images_len++] = e;
				remap_wall_entities(md, e, GROUND_TILESET_PATH, pos);
			}
			i++;
			pos.x++;
		}
		pos.y++;
		i++;
	}
	md->images[md->images_len] = NULL;
}
