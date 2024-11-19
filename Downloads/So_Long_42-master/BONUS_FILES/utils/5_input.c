/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:33:59 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 17:04:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

char	map_keycode_to_char(int keycode)
{
	if (keycode == NUM_0_KEY)
		return ('0');
	if (keycode == NUM_1_KEY)
		return ('1');
	if (keycode == NUM_2_KEY)
		return ('2');
	if (keycode == NUM_3_KEY)
		return ('3');
	if (keycode == NUM_4_KEY)
		return ('4');
	if (keycode == NUM_5_KEY)
		return ('5');
	if (keycode == NUM_6_KEY)
		return ('6');
	if (keycode == NUM_7_KEY)
		return ('7');
	if (keycode == NUM_8_KEY)
		return ('8');
	if (keycode == NUM_9_KEY)
		return ('9');
	if (keycode == ESC_KEY)
		return ('\0');
	return ('Q');
}

int	handle_key_press(int keycode, t_md *md)
{
	if (keycode >= 0 && keycode < 512)
	{
		if (keycode == ESC_KEY)
		{
			mlx_destroy_window(md->mlx, md->win);
			stop_sound(md->bgrnd_au);
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
