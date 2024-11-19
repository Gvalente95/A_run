/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_delete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:47:08 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 17:04:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_ent	*get_ent_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, t_ent_type type)
{
	int	i;

	i = 0;
	while (ents[i])
	{
		if (ents[i]->is_active && \
			is_in_pos(pos, size, ents[i]->pos, ents[i]->size) \
			&& (ents[i]->type == type || (int)type == -1))
			return (ents[i]);
		i++;
	}
	return (NULL);
}

int	delete_at_index(int index, t_ent **ents, int len)
{
	if (index > len || !ents[index])
		return (len);
	while (index < len - 1)
	{
		ents[index] = copy_ent(ents[index + 1]);
		index++;
	}
	ents[len - 1] = NULL;
	return (--len);
}

int	del_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int *ents_len)
{
	int	i;
	int	deleted_amount;

	deleted_amount = 0;
	i = -1;
	if (*ents_len == 1 && is_in_pos(pos, size, ents[0]->pos, ents[0]->size))
	{
		free(ents[0]);
		ents[0] = NULL;
		*ents_len = 0;
		return (1);
	}
	else
	{
		while (++i < *ents_len)
		{
			if (ents[i] != NULL && is_in_pos(pos, size, ents[i]->pos, \
					ents[i]->size))
				*ents_len = delete_at_index(i, ents, *ents_len);
		}
	}
	return (deleted_amount);
}

int	delete_type(t_ent_type type, t_ent **ents, int *ents_len)
{
	int	i;
	int	deleted_amount;

	deleted_amount = 0;
	i = -1;
	while (++i < *ents_len)
	{
		if (ents[i] != NULL && ents[i]->type == type)
			*ents_len = delete_at_index(i, ents, *ents_len);
	}
	return (deleted_amount);
}

t_ent	*get_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (ents[i] != NULL && is_in_pos(pos, size, ents[i]->pos, \
				ents[i]->size))
			return (ents[i]);
	}
	return (NULL);
}
