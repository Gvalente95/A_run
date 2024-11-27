/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:21:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/27 22:55:41 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	iterate_action(char *command, int amount, t_data *data, t_pile *check_size)
{
	int	i;

	i = 0;
	while (i < amount && check_size->size)
	{
		handle_instruction(command, data, 0);
		i++;
	}
	return (i);
}

void	merge_sort(t_data *data)
{
	int	start_rank;

	start_rank = data->pile_a.elements[0].rank;
	while (data->pile_a.elements[data->pile_a.size - 1].rank != start_rank)
	{
		iterate_action("pb", 3, data, &data->pile_a);
		printf("0[%d] 1[%d] 2[%d]", data->pile_b.elements[0].rank, data->pile_b.elements[1].rank, data->pile_b.elements[2].rank);
		sort_three_in_b(data, &data->pile_b);
		iterate_action("pa", 3, data, &data->pile_a);
		iterate_action("rra", 3, data, &data->pile_a);
	}
	exit(0);
}
