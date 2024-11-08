/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:42:36 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 16:42:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	render_player(t_mlx_data *mlx_data)
{
	t_ent	*player;
	void	*frame_to_draw;
	void	*color_image;

	player = &mlx_data->player;
	if (player->flip_x)
		frame_to_draw = player->cur_frame_x;
	else
		frame_to_draw = player->cur_frame;
	color_image = mlx_new_image(mlx_data->mlx, player->size.x, player->size.y);
	copy_image_data(mlx_data, frame_to_draw, color_image, player->size);

	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		color_image, player->pos.x, player->pos.y);
}

void	render_game_mobs(t_mlx_data *mlx_data)
{
	t_ent	*mob;
	int		i;

	sort_game_entities_by_z_pos(mlx_data->game_mobs, MOB_AMOUNT);
	i = -1;
	while (++i < MOB_AMOUNT)
	{
		mob = &mlx_data->game_mobs[i];
		if (mob->flip_x)
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
			mob->cur_frame_x, mob->pos.x, mob->pos.y);
		else
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
			mob->cur_frame, mob->pos.x, mob->pos.y);
	}
}

void render_env(t_mlx_data *mlx_data)
{
	t_ent *e;
	int i;

	i = -1;
	while (++i < ENV_AMOUNT)
	{
		e = &mlx_data->env[i];
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
			e->cur_frame, e->pos.x, e->pos.y);
	}
}

void	render_images(t_mlx_data *mlx_data)
{
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	mlx_data->background_color, 0, 0);
	// mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	//  		mlx_data->background_img, 0,0);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	 		mlx_data->ground, 0, WIN_H - 200);
	render_env(mlx_data);
	render_game_mobs(mlx_data);
	render_player(mlx_data);
}
