/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:33:59 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 04:52:41 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

int	handle_key_press(int keycode, t_md *md)
{
	if (keycode >= 0 && keycode < 512)
	{
		if (keycode == ESC_KEY)
		{
			mlx_destroy_window(md->mlx, md->win);
			free_md(md);
			exit(0);
		}
		md->key_prs[keycode] = 1;
		md->key_clicked = keycode;
	}
	return (0);
}

int	handle_key_release(int keycode, t_md *md)
{
	if (keycode >= 0 && keycode < 512)
	{
		md->key_prs[keycode] = 0;
	}
	return (0);
}

void	reset_mlx_values(t_md *md)
{
	md->key_clicked = -1;
	md->mouse_clicked = 0;
}
