/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_free_md.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 04:32:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 05:01:56 by giuliovalen      ###   ########.fr       */
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

int	free_void_array(void **elements, int i)
{
	if (!elements)
		return (0);
	while (elements[i])
	{
		free_void(elements[i]);
		i++;
	}
	free(elements);
	return (i);
}

void	free_ent(t_ent *ent)
{
	free_void(ent->anim_frames);
	free_void((void *)(ent->frame_path));
	free_void(ent->cur_frame);
	free(ent);
	ent = NULL;
}

int	free_ents(t_ent **ents)
{
	int	i;

	if (!ents)
		return (0);
	i = 0;
	while (ents[i])
	{
		if (ents[i])
			free_ent(ents[i]);
		i++;
	}
	free(ents);
	ents = NULL;
	return (i);
}

int	free_md(t_md *md)
{
	int	free_count;

	free_count = 0;
	free_count += free_ents(md->images);
	free_count += free_ents(md->all_images);
	free_count += free_void_array(md->env_images, 0);
	free_count += free_void_array((void **)md->coin_paths, 0);
	free_count += free_void_array((void **)md->ftstp_paths, 0);
	free_count += free_void(md->mlx);
	free_count += free_void(md->addr);
	free_count += free_void(md->bgrnd_img);
	free_count += free_void(md->map.buffer);
	ft_printf("freed stuff: %d", free_count);
	return (free_count);
}
