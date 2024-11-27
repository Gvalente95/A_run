/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:55:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/27 06:45:03 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**set_new_argv(int len, char ***argv, char **args)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		print_and_quit(NULL);
	new_argv[0] = ft_strdup((*argv)[0]);
	if (!new_argv[0])
		print_and_quit(NULL);
	i = -1;
	while (++i < len)
	{
		new_argv[i + 1] = ft_strdup(args[i]);
		if (!new_argv[i + 1])
			print_and_quit(NULL);
	}
	new_argv[len + 1] = NULL;
	return (new_argv);
}

int	get_args(char ***argv)
{
	int		i;
	int		len;
	char	**args;
	char	**new_argv;

	args = ft_split((*argv)[1], ' ');
	len = 0;
	while (args[len])
		len++;
	new_argv = set_new_argv(len, argv, args);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	*argv = new_argv;
	return (len + 1);
}

int	free_char_array(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

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
	set_values_ranks(&data, 0, 0, 0);
	if (data.pile_a.size <= 70)
		mini_sort(&data, 0, 0, 0);
	else
		radix_sort(&data, 0, 0, 0);
	print_commands(&data);
	return (free_data(&data));
}
