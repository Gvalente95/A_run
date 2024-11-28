/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:53:38 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/28 01:49:56 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <time.h>

char	**sort_arguments(int sorted, int amount, int i)
{
	int		*values;
	char	**arguments;
	int		new_val;

	srand(time(0));
	arguments = malloc(sizeof(char *) * amount);
	values = malloc(sizeof(int) * amount);
	i = 0;
	while (i < amount)
	{
		if (sorted)
			new_val = i;
		else
		{
			new_val = ((long)rand() * 2 - RAND_MAX) % INT_MAX;
			while (is_contained(new_val, values, i - 1))
				new_val = rand() % 50000;
		}
		values[i] = new_val;
		arguments[i] = ft_strdup(ft_itoa(values[i]));
		i++;
	}
	free(values);
	return (arguments);
}

void	make_tests(t_data *d, int (*f)(t_data *, int, int, int), \
	int am, char **args)
{
	init_data(d, am, args, d->visualize);
	set_values_ranks(&d->pile_a, 0, 0, 0);
	f(d, 0, 0, 0);
	print_vals(*d, 5, 0);
}

void	multiple_algo_tests(int amount, int visualize, char **arguments)
{
	t_data	r_d;
	t_data	s_d;
	t_data	m_d;

	r_d.visualize = visualize;
	s_d.visualize = visualize;
	m_d.visualize = visualize;
	r_d.algo_name = ft_strdup("RADIX");
	s_d.algo_name = ft_strdup("SELECTION_SORT");
	m_d.algo_name = ft_strdup("MERGE_SORT");
	make_tests(&m_d, mini_sort, amount, arguments);
	make_tests(&r_d, radix_sort, amount, arguments);
	make_tests(&s_d, selection_sort, amount, arguments);
	printf("LEN ARR: %d\n", r_d.pile_a.size);
	printf("RADIX:    cmds[%d] - sorted[%d]\n", \
		r_d.cmd_len, is_sorted(r_d));
	printf("MINI_SORT: cmds[%d] - sorted[%d]\n", \
		m_d.cmd_len, is_sorted(m_d));
	printf("SEL_SORT: cmds[%d] - sorted[%d]\n", \
		s_d.cmd_len, is_sorted(s_d));
	free(r_d.algo_name);
	free(s_d.algo_name);
	free(m_d.algo_name);
}

int	main(int argc, char *argv[])
{
	char	**arguments;
	int		amount;
	int		visualize;

	amount = 50;
	visualize = 1;
	if (argc >= 2)
		amount = ft_atoi(argv[1]);
	if (argc >= 3)
		visualize = ft_atoi(argv[2]);
	arguments = sort_arguments(0, amount, 0);
	multiple_algo_tests(amount, visualize, arguments);
}
