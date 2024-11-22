/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_entities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:03:00 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 02:15:45 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_ent	*copy_ent(t_ent *e)
{
	t_ent	*new_ent;

	new_ent = malloc(sizeof(t_ent));
	if (!new_ent)
		return (NULL);
	ft_memcpy(new_ent, e, sizeof(t_ent));
	set_vec3(&new_ent->pos, e->pos.x, e->pos.y, e->pos.z);
	new_ent->type = e->type;
	return (new_ent);
}

void	**get_images(t_md *d, t_ent *e, char **paths, t_vec2 size)
{
	void	**hld;
	int		i;
	int		amount;

	if (!paths)
		return (NULL);
	amount = 0;
	while (paths[amount])
		amount++;
	hld = malloc(sizeof(void *) * (amount + 1));
	if (!hld)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		hld[i] = add_img(paths[i], &e->size.x, &e->size.y, d->mlx);
		hld[i] = scale_img(d->mlx, hld[i], &e->size, size);
		i++;
	}
	hld[i] = NULL;
	return (hld);
}

void	swap_game_entities(t_ent *a, t_ent *b)
{
	t_ent	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_ents_by_z(t_ent **game_entities, int count)
{
	int	i;
	int	j;
	int	swapped;

	if (count <= 1)
		return ;
	i = -1;
	while (++i < count - 1)
	{
		swapped = 0;
		j = -1;
		while (++j < count - i - 1)
		{
			if (game_entities[j] == NULL || game_entities[j + 1] == NULL)
				continue ;
			if (game_entities[j]->pos.z < game_entities[j + 1]->pos.z)
			{
				swap_game_entities(game_entities[j], game_entities[j + 1]);
				swapped = 1;
			}
		}
		if (!swapped)
			break ;
	}
}

void	set_ent_to_mouse(t_ent *ent, t_md *md)
{
	ent->movement.x = 0;
	ent->movement.y = 0;
	ent->pos.x = md->mouse_pos.x - (ent->size.x / 2);
	ent->pos.y = md->mouse_pos.y - (ent->size.y / 2);
	ent->base_pos = ent->pos;
}
