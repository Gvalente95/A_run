/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:01:28 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/27 22:08:59 by giuliovalen      ###   ########.fr       */
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

	if (argc <= 1)
		return (0);
	init_data(&data, argc, argv, 0);
	execute_instructions(&data);
	if (is_sorted(data) && data.pile_b.size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	free_data(&data);
	return (0);
}
