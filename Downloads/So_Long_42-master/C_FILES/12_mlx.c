/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:02:25 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/10 18:03:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void reset_mlx_values(t_mlx_data *mlx_data)
{
	mlx_data->clicked = 0;
	mlx_data->mouse_prv = mlx_data->mouse_button;
	if (mlx_data->mouse_button != MOUSE_DPRESS)
		mlx_data->mouse_button = 0;
	mlx_data->last_key_pressed = '.';
}