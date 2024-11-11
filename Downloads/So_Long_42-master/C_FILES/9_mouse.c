/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:57:28 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/11 08:19:50 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	mouse_event_handler(int button, int x, int y, void *param)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)param;
	mlx_data->mouse_button = button;
	mlx_data->mouse_pos[0] = x;
	mlx_data->mouse_pos[1] = y;
	return (0);
}

int	mouse_release_handler(int button, int x, int y, void *param)
{
	t_mlx_data	*mlx_data;

	(void)x;
	(void)y;
	(void)button;
	mlx_data = (t_mlx_data *)param;
	mlx_data->mouse_button = 0;
	mlx_data->clicked = 1;
	return (0);
}

int	mouse_motion_handler(int x, int y, void *param)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)param;
	mlx_data->mouse_pos[0] = x;
	mlx_data->mouse_pos[1] = y;
	return (0);
}

void	update_mouse(t_mlx_data *mlx_data)
{
	if (mlx_data->mouse_button == MOUSE_DPRESS)
		set_ent_to_mouse(&mlx_data->player, mlx_data);
}

void	init_mouse(t_mlx_data *mlx_data)
{
	mlx_data->clicked = 0;
	mlx_mouse_hook(mlx_data->win, mouse_event_handler, mlx_data);
	mlx_hook(mlx_data->win, 5, 0, mouse_release_handler, mlx_data);
	mlx_hook(mlx_data->win, 6, 0, mouse_motion_handler, mlx_data);
}
