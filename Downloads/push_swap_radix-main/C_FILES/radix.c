/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:39:44 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/27 01:58:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <math.h>

int	get_max_len(t_data data)
{
	int	max_value;
	int	max_len;
	int	i;

	max_value = 0;
	max_len = 0;
	i = 0;
	while (i < data.pile_a.size)
	{
		if (data.pile_a.elements[i].rank > max_value)
			max_value = data.pile_a.elements[i].rank;
		i++;
	}
	while (max_value > 0)
	{
		max_len++;
		max_value >>= 1;
	}
	return (max_len);
}

int	radix_sort(t_data *data, int max_len, int digit_pos, int processed)
{
	int		initial_size;
	int		bit_value;

	max_len = get_max_len(*data);
	digit_pos = -1;
	while (++digit_pos < max_len)
	{
		initial_size = data->pile_a.size;
		processed = 0;
		while (processed < initial_size)
		{
			bit_value = ((data->pile_a.elements[data->pile_a.size - 1].rank >> \
				digit_pos) & 1);
			if (!bit_value)
				handle_instruction("pb", data, 0);
			else
				handle_instruction("ra", data, 0);
			processed++;
		}
		while (data->pile_b.size > 0)
			handle_instruction("pa", data, 0);
		if (is_sorted(*data))
			return (1);
	}
	return (1);
}
