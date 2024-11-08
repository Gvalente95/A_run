/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:33:59 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 08:47:44 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int handle_key_press(int keycode, t_mlx_data *mlx_data)
{
    if (keycode >= 0 && keycode < 512)
    {
        if (keycode == Q_KEY)
        {
            mlx_destroy_window(mlx_data->mlx, mlx_data->win);
            exit(0);
        }
        mlx_data->key_state[keycode] = 1;
        mlx_data->last_key_pressed = keycode;
        //ft_printf("Key %d pressed\n", keycode);
    }
    return (0);
}

int handle_key_release(int keycode, t_mlx_data *mlx_data)
{
    if (keycode >= 0 && keycode < 512)
    {
        mlx_data->key_state[keycode] = 0;
        ft_printf("Key %d released\n", keycode);
    }
    return (0);
}