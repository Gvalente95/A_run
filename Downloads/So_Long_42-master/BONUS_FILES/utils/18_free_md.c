/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_free_md.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 04:32:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 02:54:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	free_void(void *elem)
{
	if (!elem)
		return (0);
	free(elem);
	elem = NULL;
	return (1);
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
	int	free_count;

	free_count = 0;
	if (ent)
	{
		free_count += free_void_array(ent->anim_frames, 0);
		free_count += free_void_array((void *)ent->frame_path, 0);
		free_count += free_void_array(ent->idl_frm, 0);
		free_count += free_void_array(ent->wlk_frm, 0);
		free_count += free_void_array(ent->fly_frm, 0);
		free(ent);
		ent = NULL;
		return (free_count + 1);
	}
	return (0);
}

int	free_ents(t_ent **ents)
{
	int	freed_count;
	int	i;

	if (!ents)
		return (0);
	i = 0;
	freed_count = 0;
	while (ents[i])
	{
		freed_count += free_ent(ents[i]);
		ents[i] = NULL;
		i++;
	}
	free(ents);
	ents = NULL;
	ft_printf("%d entities and %d images \
		successfully freed\n", i, freed_count);
	return (freed_count + i + 1);
}

int	free_md(t_md *md)
{
	int	free_count;

	ft_printf("images to free: %d\n", md->images_len);
	free_count = 0;
	free_count += free_ents(md->images);
	free_count += free_ents(md->all_images);
	free_count += free_particles(md, md->particles);
	free_count += free_void_array(md->env_images, 0);
	free_count += free_void(md->bgrnd_img);
	free_count += free_void(md->map.buffer);
	free_count += free_void_array(md->plr.fly_frm, 0);
	free_count += free_void_array(md->plr.wlk_frm, 0);
	free_count += free_void_array(md->plr.idl_frm, 0);
	mlx_destroy_window(md->mlx, md->win);
	free_count += free_void(md->mlx);
	ft_printf("Freed: %d elements\n", free_count);
	return (free_count);
}
