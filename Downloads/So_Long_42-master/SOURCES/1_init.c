/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:29:47 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/09 01:15:40 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	init_mlx_data(t_mlx_data *mlx_data)
{
	int	i;

	i = -1;
	while (++i < 512)
		mlx_data->key_state[i] = 0;
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		return (printf("Error initializing MLX\n"), 0);
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIN_W, WIN_H, "g");
	if (!mlx_data->win)
		return (printf("Error creating window\n"), 0);
	mlx_data->background_color = mlx_new_image(mlx_data->mlx, WIN_W, WIN_H);
	if (!mlx_data->background_color)
		return (printf("Error creating background image\n"), 0);
	mlx_data->addr = mlx_get_data_addr(mlx_data->background_color, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	set_img_color(get_Vec2(mlx_data->size.x, mlx_data->size.y), mlx_data->background_color, COLOR_BLUE, 1);
	mlx_data->god_mode = 0;
	mlx_data->mouse_button = 0;
	mlx_data->background_img = add_img(BACKGROUND_SPRITE_PATH, \
		&mlx_data->size.x, &mlx_data->size.y, mlx_data->mlx);
	mlx_data->ground = add_img(GROUND_SPRITES_PATH, &mlx_data->size.x, \
		&mlx_data->size.y, mlx_data->mlx);
	return (1);
}

int	init_game_mobs(t_mlx_data *mlx_data, char *frames_path, int ammount)
{
	t_ent	*ent;
	char	**idl_frms;
	char	**wlk_frm;
	int		i;

	idl_frms = get_frames_paths(frames_path, "IDLE_", 2);
	wlk_frm = get_frames_paths(frames_path, "WALK_", 2);
	i = -1;
	while (++i < ammount)
	{
		ent = &mlx_data->game_mobs[i];
		ent->type = mob;
		ent->is_grounded = 1;
		ent->flip_x = 0;
		ent->walk_frame_amount = 2;
		ent->idle_frame_amount = 2;
		set_Vec3(&ent->pos, rand_range(0, WIN_W), 0, 1);
		set_Vec3(&ent->movement, rand_range(-1, 2), rand_range(-1, 2), 0);
		set_entity_frames(mlx_data, &mlx_data->game_mobs[i], wlk_frm, idl_frms);
	}
	free(idl_frms);
	free(wlk_frm);
	return (1);
}

int	init_player(t_mlx_data *mlx_data, char *frames_path)
{
	char	**idle_frames;
	char	**wlk_frm;
	t_ent	*player;

	player = &mlx_data->player;
	player->is_grounded = 1;
	player->flip_x = 0;
	player->jumps = 2;
	player->jet_sky_timer = 0;
	set_Vec3(&player->pos, WIN_W / 2, 0, 0);
	set_Vec3(&player->movement, 0, 0, 0);
	set_Vec2(&player->size, 50, 50);
	player->type = Player;
	idle_frames = get_frames_paths(frames_path, "IDLE_", 2);
	wlk_frm = get_frames_paths(frames_path, "WALK_", 2);
	player->walk_frame_amount = 2;
	player->idle_frame_amount = 2;
	set_entity_frames(mlx_data, &mlx_data->player, wlk_frm, idle_frames);
	return (1);
}

int	init_env(t_mlx_data *mlx_data, int i, int r)
{
	int		z_pos;
	t_ent	*e;
	t_Vec2	size[4];
	void	*imgs[4];
	char	**frames;

	frames = get_frames_paths(WALL_SPRITES_PATH, "WALL_", 4);
	i = -1;
	while (++i < 4)
		imgs[i] = add_img(frames[i], &size[i].x, &size[i].y, mlx_data->mlx);
	i = -1;
	while (++i < ENV_AMOUNT)
	{
		z_pos = rand_range(0, 5);
		if (z_pos == 1)
			z_pos = 0;
		e = &mlx_data->env[i];
		r = rand_range(0, 3);
		set_Vec3(&e->pos, rand_range(0, WIN_W - size[r].x), \
			rand_range(0, WIN_H - size[r].y), z_pos);
		set_Vec3(&e->movement, 0, 0, 0);
		e->size = size[r];
		e->jet_sky_timer = 0;
		e->type = env;
		e->cur_frame = mlx_new_image(mlx_data->mlx, size[r].x, size[r].y);
		copy_image_data(mlx_data, imgs[r], e->cur_frame, size[r]);
		if (e->pos.z > 0)
			set_brightness(e->size.x, e->size.y, e->cur_frame, .5 - (z_pos * 0.1));
	}
	free(frames);
	return (1);
}

int	init_game_entities(t_mlx_data *mlx_data)
{
	init_player(mlx_data, PLAYER_SPRITES_PATH);
	init_game_mobs(mlx_data, MOB_SPRITES_PATH, MOB_AMOUNT);
	init_env(mlx_data, 0, 0);
	return (1);
}
