/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:02:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/28 15:15:49 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_pile_sorted(t_pile pile)
{
	int	i;

	i = 0;
	while (i < pile.size)
	{
		if (pile.elements[i].val < pile.elements[i + 1].val)
			return (0);
		i++;
	}
	return (1);
}

int	sort_five_in_a(t_data *data)
{
	push_smallest_to_b(data);
	push_smallest_to_b(data);
	if (!is_pile_sorted(data->pile_a))
		sort_three_in_a(data);
	handle_instruction("pa", data, 0);
	handle_instruction("pa", data, 0);
	return (5);
}

int	sort_four_in_a(t_data *data)
{
	push_smallest_to_b(data);
	sort_three_in_a(data);
	handle_instruction("pa", data, 0);
	return (4);
}

int	mini_sort(t_data *d, int size, int i, int res)
{
	(void)i;
	size = d->pile_a.size;
	if (is_sorted(*d))
		return (1);
	if (size == 2)
		handle_instruction("sa", d, res);
	else if (size == 3)
		sort_three_in_a(d);
	else if (size == 4)
		sort_four_in_a(d);
	else if (size == 5)
		sort_five_in_a(d);
	else
	{
		while (d->pile_a.size > 5)
			push_smallest_to_b(d);
		sort_five_in_a(d);
		while (d->pile_b.size)
			handle_instruction("pa", d, i);
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
