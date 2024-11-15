/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:39:27 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/15 20:44:52 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	init_player_frames(t_md *md, char *path, t_ent *e)
{
	char	**idl_frm;
	char	**wlk_frm;
	char	**fly_frm;

	e->walk_frame_amount = 2;
	e->idle_frame_amount = 2;
	idl_frm = get_paths(path, "IDLE_", 2, ".png");
	wlk_frm = get_paths(path, "WALK_", 2, ".png");
	fly_frm = get_paths(path, "FLY_", 2, ".png");
	e->wlk_frm = get_images(md, e, wlk_frm, e->size);
	e->idl_frm = get_images(md, e, idl_frm, e->size);
	e->fly_frm = get_images(md, e, fly_frm, e->size);
	e->cur_frame = e->idl_frm[0];
	e->frames_amount = 2;
	set_vec2(&md->plr.start_pos, e->pos.x, e->pos.y);
	e->cur_frame_index = 0;
}

void	handle_entity_frames(t_md *md, t_ent *e, void *path, t_vec2 scale)
{
	char	**frames;
	int		frames_amount;

	frames_amount = e->frames_amount;
	frames = get_paths(path, "", frames_amount, ".png");
	e->anim_frames = malloc(sizeof(void *) * (frames_amount + 1));
	if (!e->anim_frames)
		return ;
	e->frames_amount = -1;
	while (frames[++e->frames_amount] && e->frames_amount < frames_amount)
	{
		e->anim_frames[e->frames_amount] = add_img(frames[e->frames_amount], \
			&e->size.x, &e->size.y, md);
		if (!e->anim_frames[e->frames_amount])
			break ;
		e->anim_frames[e->frames_amount] = scale_img(md, \
			e->anim_frames[e->frames_amount], &e->size, scale);
	}
	free (frames);
}
