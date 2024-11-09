/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:39 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/09 02:25:13 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	update_and_render(t_mlx_data *mlx_data)
{
	update_mouse(mlx_data);
	mlx_data->time++;
	update(mlx_data);
	render_images(mlx_data);

	int testX = 0;
	int testY = 0;
	void *img = add_img(TEST_IMG, &testX, &testY, mlx_data);
	mlx_put_image_to_window(&mlx_data, mlx_data->win, img, 0,0);
	return (0);
}

int	main(void)
{
	t_mlx_data	mlx_data;

	mlx_data.time = 0;
	srand(time(0));
	if (!init_mlx_data(&mlx_data))
		return (1);
	if (!init_game_entities(&mlx_data))
		return (1);
	mlx_hook(mlx_data.win, KEY_PRESS, 0, handle_key_press, &mlx_data);
	mlx_hook(mlx_data.win, KEY_RELEASE, 0, handle_key_release, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, (int (*)())update_and_render, &mlx_data);
	mlx_loop(mlx_data.mlx);
	return (0);
}
