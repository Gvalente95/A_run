/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:14:11 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/27 22:52:05 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	push_smallest_to_b(t_data *data, t_pile *pile)
{
	int	values[2];
	int	smallest_rank;
	int	smallest_index;

	min_value(*pile, values);
	smallest_rank = values[0];
	smallest_index = values[1];
	while (pile->elements[pile->size - 1].rank != smallest_rank)
	{
		if (smallest_index < pile->size / 2)
			handle_instruction("rra", data, 0);
		else
			handle_instruction("ra", data, 0);
	}
	handle_instruction("pb", data, 0);
}

void	push_smallest_to_a(t_data *data, t_pile *pile)
{
	int	values[2];
	int	smallest_rank;
	int	smallest_index;

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
}

void	sort_three_in_a(t_data *data, t_pile *pile)
{
	if (pile->elements[2].rank > pile->elements[1].rank && \
		pile->elements[0].rank > pile->elements[2].rank)
		handle_instruction("sa", data, 0);
	else if (pile->elements[2].rank < pile->elements[1].rank && \
		pile->elements[0].rank < pile->elements[2].rank)
		handle_instruction("rra", data, 0);
	else if (pile->elements[2].rank > pile->elements[1].rank && \
		pile->elements[0].rank > pile->elements[1].rank)
		handle_instruction("ra", data, 0);
	else if (pile->elements[2].rank > pile->elements[1].rank && \
		pile->elements[0].rank < pile->elements[1].rank)
	{
		handle_instruction("ra", data, 0);
		handle_instruction("sa", data, 0);
	}
	else
	{
		handle_instruction("rra", data, 0);
		handle_instruction("sa", data, 0);
	}
}

void	sort_three_in_b(t_data *data, t_pile *pile)
{
	if (pile->elements[2].rank > pile->elements[1].rank && \
		pile->elements[0].rank > pile->elements[2].rank)
		handle_instruction("sb", data, 0);
	else if (pile->elements[2].rank < pile->elements[1].rank && \
		pile->elements[0].rank < pile->elements[2].rank)
		handle_instruction("rrb", data, 0);
	else if (pile->elements[2].rank > pile->elements[1].rank && \
		pile->elements[0].rank > pile->elements[1].rank)
		handle_instruction("rb", data, 0);
	else if (pile->elements[2].rank > pile->elements[1].rank && \
		pile->elements[0].rank < pile->elements[1].rank)
	{
		handle_instruction("rb", data, 0);
		handle_instruction("sb", data, 0);
	}
	else
	{
		handle_instruction("rrb", data, 0);
		handle_instruction("sb", data, 0);
	}
}
