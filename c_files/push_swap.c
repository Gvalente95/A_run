/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:55:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/12/04 20:26:47 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(int argc, char *argv[])
{
	int		free_argv;
	t_data	data;

	if (argc <= 1)
		return (0);
	free_argv = 0;
	if (argc == 2)
	{
		argc = get_args(&argv);
		free_argv = 1;
	}
	init_data(&data, argc, argv, 0);
	if (free_argv)
		free_char_array(argv);
	if (is_sorted(data))
		return (free_data(&data));
	set_values_ranks(&data.pile_a, 0, 0, 0);
	if (data.pile_a.size <= 70)
		mini_sort(&data, 0, 0, 0);
	else
		radix_sort(&data, 0, 0, 0);
	print_commands(&data);
	return (free_data(&data));
}
