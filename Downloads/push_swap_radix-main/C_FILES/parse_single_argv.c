/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:51:22 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/29 21:51:31 by giuliovalen      ###   ########.fr       */
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
