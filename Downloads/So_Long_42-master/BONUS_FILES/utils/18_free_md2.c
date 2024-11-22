/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_free_md2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 02:48:05 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 02:05:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	free_particles(t_md *md, t_prt **prts)
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
			mlx_destroy_image(md->mlx, prts[i]->cur_frame);
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
	ft_printf("%d particles and images		\
successfully freed\n", freed_count + 1);
	return (freed_count + 1);
}
