/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:02:07 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/27 22:34:43 by giuliovalen      ###   ########.fr       */
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

void	sort_five_in_a(t_data *data, t_pile *pile)
{
	push_smallest_to_b(data, pile);
	push_smallest_to_b(data, pile);
	if (!is_pile_sorted(*pile))
		sort_three_in_a(data, pile);
	handle_instruction("pa", data, 0);
	handle_instruction("pa", data, 0);
}

void	sort_five_in_b(t_data *data, t_pile *pile)
{
	push_smallest_to_a(data, pile);
	push_smallest_to_a(data, pile);
	if (!is_pile_sorted(*pile))
		sort_three_in_b(data, pile);
	handle_instruction("pb", data, 0);
	handle_instruction("pb", data, 0);
}

int	mini_sort(t_data *d, int size, int i, int res)
{
	size = d->pile_a.size;
	if (is_sorted(*d))
		return (1);
	if (size == 2)
		handle_instruction("sa", d, res);
	else if (size == 3)
		sort_three_in_a(d, &d->pile_a);
	else if (size == 4)
	{
		push_smallest_to_b(d, &d->pile_a);
		if (!is_pile_sorted(d->pile_a))
			sort_three_in_a(d, &d->pile_a);
		handle_instruction("pa", d, i);
	}
	else if (size == 5)
		sort_five_in_a(d, &d->pile_a);
	else
	{
		merge_sort(d);
		// while (d->pile_a.size > 5)
		// 	push_smallest_to_b(d, &d->pile_a);
		// sort_five_in_a(d, &d->pile_a);
		// while (d->pile_b.size)
		// 	handle_instruction("pa", d, i);
	}
	return (1);
}
