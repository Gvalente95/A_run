/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_map_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:15:24 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 17:04:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	close_and_quit(char *error_msg, int fd)
{
	ft_printf("%s", error_msg);
	if (fd != -1)
		close(fd);
	exit(0);
}

int	verify_map_borders(char *buffer, int width, int height)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			while (buffer[i] == '\n')
				i++;
			if ((y == 0 || y == height - 1 || x == 0 || \
				x == width - 1) && buffer[i] != '1')
				close_and_quit("Error\nBorder with no wall", -1);
			x++;
			i++;
		}
		y++;
	}
	return (1);
}

t_vec2	get_map_dimensions(char *map, int i, int current_width, t_vec2 res)
{
	set_vec2(&res, 0, 0);
	current_width = 0;
	i = -1;
	while (map[++i])
	{
		if (map[i] == '\n')
		{
			if (res.y == 0)
				current_width = res.x;
			else if (res.x != current_width)
				close_and_quit("Error\nline size.", -1);
			set_vec2(&res, 0, res.y + 1);
		}
		else
			res.x++;
	}
	if (res.x > 0)
	{
		if (res.y > 0 && res.x != current_width)
			close_and_quit("Error\nline sizes", -1);
		res.y++;
	}
	res.x = current_width;
	return (res);
}

char	*get_map_buffer(int fd, int check_for_error)
{
	char	*buffer;
	char	*line;
	char	*temp;
	int		len;

	buffer = ft_strdup("");
	line = get_next_line(fd);
	if (!line)
		close_and_quit("Error\nEmpty map", fd);
	while (line != NULL)
	{
		temp = buffer;
		len = ft_strlen(line);
		if (check_for_error && line[len - 2] != '1')
			close_and_quit("Error\nunclosed map", -1);
		buffer = ft_strjoin(buffer, line);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	return (buffer);
}

t_vec2	get_indexes(char *buffer)
{
	t_vec2	positions;
	int		i;

	i = 0;
	set_vec2(&positions, -1, -1);
	while (buffer[i++])
	{
		if (buffer[i] == 'P')
			positions.x = i;
		if (buffer[i] == 'E')
			positions.y = i;
		if (positions.x >= 0 && positions.y >= 0)
			break ;
	}
	return (positions);
}
