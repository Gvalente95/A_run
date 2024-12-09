/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:01:28 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/12/09 16:55:58 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

#include <stdlib.h>

void	execute_instructions(t_data *data)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL && line[0] != '\n')
	{
		if (handle_instruction(line, data, 0) == -1)
		{
			free(line);
			print_and_quit(data);
		}
		free(line);
		data->cmd_len = 0;
		line = get_next_line(0);
	}
	free(line);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		free_argv;

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
	execute_instructions(&data);
	if (is_sorted(data) && data.pile_b.size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	free_data(&data);
	return (0);
}
