/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:03:49 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/12/04 20:12:09 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_arg_valid(t_data *data, char *arg)
{
	long	result;
	int		i;

	i = 0;
	if (arg[i] == '-')
		i++;
	if (!arg[i])
		print_and_quit(data);
	while (arg[i])
		if (!ft_isdigit(arg[i++]))
			print_and_quit(data);
	result = ft_atol(arg);
	if (result > INT_MAX || result < INT_MIN)
		print_and_quit(data);
	return ((int)result);
}

void	check_for_doublons(t_data *data, int argc, char *argv[])
{
	int	i;
	int	j;

	i = data->pile_a.size - 1;
	while (i >= 0)
	{
		data->pile_a.elements[i].val = is_arg_valid(data, argv[argc - 1]);
		j = i + 1;
		while (j < data->pile_a.size)
		{
			if (data->pile_a.elements[j].val == data->pile_a.elements[i].val)
				print_and_quit(data);
			j++;
		}
		data->pile_a.elements[i].rank = -1;
		argc--;
		i--;
	}
}

void	init_data(t_data *data, int argc, char *argv[], int visualize)
{
	data->pile_a.elements = NULL;
	data->pile_b.elements = NULL;
	data->cmd_buff = NULL;
	data->pile_a.size = argc - 1;
	data->pile_b.size = 0;
	data->cmd_len = 0;
	data->visualize = visualize;
	data->pile_a.elements = malloc(sizeof(t_element) * (argc - 1));
	data->pile_b.elements = malloc(sizeof(t_element) * (argc - 1));
	data->cmd_buff = malloc(sizeof(char *) * (data->pile_a.size * 2000));
	if (!data->pile_a.elements || !data->pile_b.elements || !data->cmd_buff)
		print_and_quit(data);
	if (!arg_doublons_checker(data, argv, argc))
		print_and_quit(data);
}

int	is_contained(int value, int *values, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (value == values[i])
			return (1);
		i++;
	}
	return (0);
}

int	arg_doublons_checker(t_data *data, char **args, int len)
{
	int	i;
	int	j;
	int	data_index;

	i = 1;
	data_index = data->pile_a.size - 1;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(args[i], args[j]) == 0)
				return (0);
			j++;
		}
		data->pile_a.elements[data_index].val = is_arg_valid(data, args[i]);
		data->pile_a.elements[data_index].rank = -1;
		data_index--;
		i++;
	}
	return (1);
}
