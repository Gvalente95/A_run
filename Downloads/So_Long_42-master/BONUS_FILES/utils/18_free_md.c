/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_free_md.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 04:32:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 06:03:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

int	free_void(void *elem)
{
	if (!elem)
		return (0);
	free(elem);
	elem = NULL;
	return (1);
}

int	destroy_images(t_md *md, void **images)
{
	int	i;
	int	free_count;

	if (!images)
		return (0);
	free_count = 0;
	i = 0;
	while (images[i])
	{
		mlx_destroy_image(md, images[i]);
		free_count++;
	}
	return (free_count);
}

int	free_void_array(void **elements, int i)
{
	int	free_count;

	free_count = 0;
	if (!elements)
		return (0);
	while (elements[i])
	{
		free_count += free_void(elements[i]);
		i++;
	}
	free(elements);
	return (free_count + 1);
}

int	free_ent(t_ent *ent)
{
	if (ent)
	{
		free_void(ent->anim_frames);
		free_void((void *)(ent->frame_path));
		free_void(ent->cur_frame);
		free(ent);
		ent = NULL;
		return (1);
	}
	return (0);
}

int	free_ents(t_ent **ents, t_md *md)
{
	int	freed_count;
	int	i;

	if (!ents)
		return (0);
	i = 0;
	freed_count = 0;
	while (ents[i])
	{
		if (ents[i])
		{
			free_void(ents[i]->anim_frames);
			free_void((void *)(ents[i]->frame_path));
			mlx_destroy_image(md, ents[i]->cur_frame);
			free(ents[i]);
			ents[i] = NULL;
		}
		freed_count += free_ent(ents[i]);
		i++;
	}
	free(ents);
	ents = NULL;
	return (freed_count);
}

int	free_md(t_md *md)
{
	int	free_count;

	free_count = 0;
	free_count += free_ents(md->images, md);
	free_count += free_ents(md->all_images, md);
	free_count += destroy_images(md, md->env_images);
	free_count += free_void_array((void **)md->coin_paths, 0);
	free_count += free_void_array((void **)md->ftstp_paths, 0);
	free_count += free_void(md->addr);
	free_count += free_void(md->bgrnd_img);
	free_count += free_void(md->map.buffer);
	free_count += destroy_images(md, md->plr.fly_frm);
	free_count += destroy_images(md, md->plr.wlk_frm);
	free_count += destroy_images(md, md->plr.idl_frm);
	free_count += free_void(md->mlx);
	ft_printf("freed stuff: %d", free_count);
	return (free_count);
}
