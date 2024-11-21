/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_audio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 04:54:44 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 03:00:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pid_t	play_random_sound(const char *path, int len, const char *format)
{
	pid_t	sound;
	char	*with_index;
	char	*fullpath;
	char	*index_str;
	int		index;

	index = r_range(0, len - 1);
	index_str = ft_itoa(index);
	with_index = ft_strjoin(path, index_str);
	free(index_str);
	fullpath = ft_strjoin(with_index, format);
	free(with_index);
	sound = play_sound(fullpath, 0);
	free(fullpath);
	return (sound);
}

pid_t	play_sound(const char *filename, int loop)
{
	pid_t	pid;

	(void)loop;
	pid = fork();
	if (pid == 0)
	{
		if (execlp("afplay", "afplay", filename, (char *) NULL) == -1)
		{
			perror("execlp failed");
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}

void	stop_sound(pid_t pid)
{
	if (pid > 0)
		kill(pid, SIGTERM);
}

int	is_audio_playing(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, WNOHANG) == 0)
		return (1);
	return (0);
}
