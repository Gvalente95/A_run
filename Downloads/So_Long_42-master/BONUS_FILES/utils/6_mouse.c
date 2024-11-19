/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:57:28 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 17:04:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	mouse_event_handler(int button, int x, int y, void *param)
{
	t_md	*md;

	md = (t_md *)param;
	md->mouse_pressed = button;
	md->mouse_pos.x = x;
	md->mouse_pos.y = y;
	return (0);
}

int	mouse_release_handler(int button, int x, int y, void *param)
{
	t_md	*md;

	(void)x;
	(void)y;
	(void)button;
	md = (t_md *)param;
	md->mouse_clicked = md->mouse_pressed;
	md->mouse_pressed = 0;
	return (0);
}

int	mouse_motion_handler(int x, int y, void *param)
{
	t_md	*md;

	md = (t_md *)param;
	md->mouse_pos.x = x;
	md->mouse_pos.y = y;
	return (0);
}

void	update_mouse(t_md *md)
{
	if (md->mouse_pressed == MOUSE_DPRESS && md->key_prs[X_KEY])
		set_ent_to_mouse(&md->plr, md);
}

void	init_mouse(t_md *md)
{
	mlx_mouse_hook(md->win, mouse_event_handler, md);
	mlx_hook(md->win, 5, 0, mouse_release_handler, md);
	mlx_hook(md->win, 6, 0, mouse_motion_handler, md);
}
