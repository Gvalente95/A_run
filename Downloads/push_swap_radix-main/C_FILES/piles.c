/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:00:13 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/27 02:00:36 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	set_values_ranks(t_data *data, int i, int j, int cur_highest)
{
	t_element	*max_index;

	cur_highest = INT_MAX;
	while (i < data->pile_a.size)
	{
		max_index = NULL;
		j = 0;
		while (j < data->pile_a.size)
		{
			if (data->pile_a.elements[j].val < cur_highest && \
				data->pile_a.elements[j].rank == -1)
			{
				if (!max_index || data->pile_a.elements[j].val > max_index->val)
					max_index = &data->pile_a.elements[j];
			}
			j++;
		}
		if (!max_index)
			break ;
		max_index->rank = data->pile_a.size - i;
		cur_highest = max_index->val;
		i++;
	}
	return (0);
}

int	get_max_rank(t_pile pile)
{
	int	i;
	int	max_rank;

	max_rank = -1;
	i = 0;
	while (i < pile.size)
	{
		if (pile.elements[i].rank > max_rank)
			max_rank = pile.elements[i].rank;
		i++;
	}
	return (max_rank);
}
