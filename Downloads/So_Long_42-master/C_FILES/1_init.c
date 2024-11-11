/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:29:47 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/11 12:55:17 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

int	init_mlx_data(t_mlx_data *mlx_data, t_vec2 win_size)
{
	int	i;

	i = -1;
	while (++i < 512)
		mlx_data->key_state[i] = 0;
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		return (printf("Error initializing MLX\n"), 0);
	mlx_data->win = mlx_new_window(mlx_data->mlx, win_size.x, win_size.y, "g");
	if (!mlx_data->win)
		return (printf("Error creating window\n"), 0);
	mlx_data->background_color = mlx_new_image(mlx_data->mlx, win_size.x, win_size.y);
	if (!mlx_data->background_color)
		return (printf("Error creating background image\n"), 0);
	mlx_data->addr = mlx_get_data_addr(mlx_data->background_color, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	//set_img_color(get_Vec2(mlx_data->size.x, mlx_data->size.y), mlx_data->background_color, COLOR_BLUE, 1);
	mlx_data->god_mode = 0;
	mlx_data->mouse_button = 0;
	mlx_data->background = NULL;
	mlx_data->images_len = 0;
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
	mlx_data->game_mobs = malloc((ammount + 1) * sizeof(t_ent *));
	if (!mlx_data->game_mobs)
    {
        free(idl_frms);
        free(wlk_frm);
        return 0;
    }
	i = -1;
	while (++i < ammount)
	{
		mlx_data->game_mobs[i] = malloc(sizeof(t_ent));
		if (!mlx_data->game_mobs[i])
			break;
		ent = mlx_data->game_mobs[i];
		ent->type = mob;
		ent->is_grounded = 1;
		ent->flip_x = 0;
		ent->walk_frame_amount = 2;
		ent->idle_frame_amount = 2;
		set_Vec3(&ent->pos, rand_range(0, WIN_W), 0, 1);
		set_Vec3(&ent->movement, rand_range(-1, 2), rand_range(-1, 2), 0);
		set_entity_frames(mlx_data, mlx_data->game_mobs[i], wlk_frm, idl_frms);
	}
	mlx_data->game_mobs[i] = NULL;
	free(idl_frms);
	free(wlk_frm);
	return (1);
}

// int	init_player(t_mlx_data *mlx_data, char *frames_path, t_vec3 pos)
// {
// 	char	**idle_frames;
// 	char	**wlk_frm;
// 	t_ent	*player;

// 	player = &mlx_data->player;
// 	player->is_grounded = 1;
// 	player->flip_x = 0;
// 	player->jumps = 2;
// 	player->jet_sky_timer = 0;
// 	player->pos = pos;
// 	set_Vec3(&player->movement, 0, 0, 0);
// 	set_Vec2(&player->size, 50, 50);
// 	player->type = Player;
// 	idle_frames = get_frames_paths(frames_path, "IDLE_", 2);
// 	wlk_frm = get_frames_paths(frames_path, "WALK_", 2);
// 	player->walk_frame_amount = 2;
// 	player->idle_frame_amount = 2;
// 	set_entity_frames(mlx_data, &mlx_data->player, wlk_frm, idle_frames);
// 	return (1);
// }

int set_images(t_mlx_data *mlx_data)
{
	t_ent *e;
	int i;

	mlx_data->env = malloc(sizeof(t_ent *) * (mlx_data->images_len + 1));
	if (!mlx_data->env)
		return (0);
	i = -1;
	while (mlx_data->images[++i] && i < mlx_data->images_len)
	{
		e = mlx_data->images[i];
		if (!e)
			break;
		mlx_data->env[i] = copy_ent(e);
	}
	mlx_data->env[i] = NULL;
	return (1);
}

int	init_game_entities(t_mlx_data *mlx_data)
{
	init_player(mlx_data, PLAYER_SPRITES_PATH, get_Vec3(0, WIN_H/2, 0));
	init_game_mobs(mlx_data, MOB_SPRITES_PATH, MOB_AMOUNT);
	set_images(mlx_data);
	//int i = -1;
	// while (mlx_data->env[++i])
	// 	printf("i:%d x:%d y:%d f:%s\n", i, mlx_data->env[i]->pos.x, mlx_data->env[i]->pos.y, mlx_data->env[i]->frame_path);

	// exit(0);
	//init_env(mlx_data, 0);
	return (1);
}
