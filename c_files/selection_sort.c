/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:12:14 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/28 06:19:06 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	*max_value(t_pile pile, int *values)
{
	int	i;

	i = -1;
	values[0] = -1;
	while (++i < pile.size)
	{
		if (pile.elements[i].rank > values[0])
		{
			values[0] = pile.elements[i].rank;
			values[1] = i;
		}
	}
	return (values);
}

int	*min_value(t_pile pile, int *values)
{
	int	i;

	values[0] = INT_MAX;
	values[1] = 0;
	i = 0;
	while (i < pile.size)
	{
		if (pile.elements[i].rank < values[0])
		{
			values[0] = pile.elements[i].rank;
			values[1] = i;
		}
		i++;
	}
	return (values);
}

int	selection_sort(t_data *data, int operations, int direction, int i)
{
	(void)i;
	(void)direction;
	operations = 0;
	while (data->pile_a.size)
		push_smallest_to_b(data);
	while (data->pile_b.size)
		operations += handle_instruction("pa", data, 0);
	return (operations);
}
