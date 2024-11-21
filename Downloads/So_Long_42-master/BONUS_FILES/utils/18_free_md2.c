/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_free_md2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 02:48:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 02:59:49 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	free_particles(t_prt **prts)
{
	int	freed_count;
	int	i;

	if (!prts)
		return (0);
	i = 0;
	freed_count = 0;
	while (prts[i])
	{
		if (prts[i]->cur_frame)
		{
			free(prts[i]->cur_frame);
			prts[i]->cur_frame = NULL;
			freed_count++;
		}
		free(prts[i]);
		prts[i] = NULL;
		freed_count++;
		i++;
	}
	free(prts);
	prts = NULL;
	return (freed_count + 1);
}
