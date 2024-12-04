/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:14:11 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/28 15:11:40 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	push_smallest_to_b(t_data *data)
{
	t_pile	*pile;
	int		values[2];
	int		smallest_rank;
	int		smallest_index;
	int		rotate_amount;

	pile = &data->pile_a;
	min_value(*pile, values);
	smallest_rank = values[0];
	smallest_index = values[1];
	rotate_amount = 0;
	while (pile->elements[pile->size - 1].rank != smallest_rank)
	{
		if (smallest_index < pile->size / 2)
			rotate_amount -= handle_instruction("rra", data, 0);
		else
			rotate_amount += handle_instruction("ra", data, 0);
	}
	handle_instruction("pb", data, 0);
	return (rotate_amount);
}

int	push_smallest_to_a(t_data *data)
{
	t_pile	*pile;
	int		values[2];
	int		smallest_rank;
	int		smallest_index;

	pile = &data->pile_b;
	min_value(*pile, values);
	smallest_rank = values[0];
	smallest_index = values[1];
	while (pile->elements[pile->size - 1].rank != smallest_rank)
	{
		if (smallest_index < pile->size / 2)
			handle_instruction("rrb", data, 0);
		else
			handle_instruction("rb", data, 0);
	}
	handle_instruction("pa", data, 0);
	return (1);
}

int	sort_three_in_a(t_data *data)
{
	int	values[3];

	values[0] = data->pile_a.elements[0].rank;
	values[1] = data->pile_a.elements[1].rank;
	values[2] = data->pile_a.elements[2].rank;
	if (values[2] < values[1] && values[1] < values[0])
		return (3);
	if (values[2] > values[1] && values[0] > values[2])
		handle_instruction("sa", data, 0);
	else if (values[2] < values[1] && values[0] < values[2])
		handle_instruction("rra", data, 0);
	else if (values[2] > values[1] && values[0] > values[1])
		handle_instruction("ra", data, 0);
	else if (values[2] > values[1] && values[0] < values[1])
	{
		handle_instruction("ra", data, 0);
		handle_instruction("sa", data, 0);
	}
	else
	{
		handle_instruction("rra", data, 0);
		handle_instruction("sa", data, 0);
	}
	return (3);
}

int	sort_three_in_b(t_data *data)
{
	int	values[3];

	values[0] = data->pile_b.elements[0].rank;
	values[1] = data->pile_b.elements[1].rank;
	values[2] = data->pile_b.elements[2].rank;
	if (values[2] < values[1] && values[1] < values[0])
		return (3);
	if (values[2] > values[1] && values[0] > values[2])
		handle_instruction("sb", data, 0);
	else if (values[2] < values[1] && values[0] < values[2])
		handle_instruction("rrb", data, 0);
	else if (values[2] > values[1] && values[0] > values[1])
		handle_instruction("rb", data, 0);
	else if (values[2] > values[1] && values[0] < values[1])
	{
		handle_instruction("rb", data, 0);
		handle_instruction("sb", data, 0);
	}
	else
	{
		handle_instruction("rrb", data, 0);
		handle_instruction("sb", data, 0);
	}
	return (3);
}

int	iterate_action(char *action, int count, t_data *data, t_pile *pile)
{
	int	processed;

	processed = 0;
	while (processed++ < count && pile->size)
		handle_instruction(action, data, 0);
	return (processed);
}
