/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:08:31 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 16:58:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

char dirs[4][20] = {"up", "down", "left", "right"};
void	handle_movement(t_mlx_data *mlx_data, t_ent *e, int base_speed_x, int base_speed_y)
{
	int	adjusted_speed;
	t_Vec2 col_dir;

	col_dir = get_collisions(e, mlx_data);
	if (col_dir.x != 0)
		e->pos.x += col_dir.x;
	if (col_dir.y != 0)
		e->pos.y += col_dir.y;
	
	if (e->movement.x != 0)
	{
		adjusted_speed = base_speed_x * (abs(e->movement.x) / (float)MV_DUR);
		if (e->movement.x > 0)
		{
			e->movement.x--;
			e->pos.x += adjusted_speed;
		}
		else if (e->movement.x < 0)
		{
			e->movement.x++;
			e->pos.x -= adjusted_speed;
		}
	}
	if (e->movement.y != 0)
	{
		adjusted_speed = base_speed_y * (abs(e->movement.y) / (float)MV_DUR);
		if (e->movement.y > 0)
		{
			e->movement.y--;
			e->pos.y += adjusted_speed;
		}
		else if (e->movement.y < 0)
		{
			e->movement.y++;
			e->pos.y -= adjusted_speed;
		}
	}
}

int	update_entity(t_ent *e, t_Vec3 frm_mv, int speed_x, int speed_y, t_mlx_data *mlx)
{
	if (mlx->key_state[UP_KEY])
		frm_mv.y = -1;
	if (e->is_grounded && e->movement.y > 0)
	{
		e->movement.y = 0;
		frm_mv.y = 0;		
	}
	else if (!e->is_grounded && mlx->time % 4 == 0)
		e->movement.y += 8;
	if (e->jump_timer > 0)
	{
		e->jump_timer--;
		if (e->jump_timer <= 0)
		{
			e->jump_timer = 0;
			e->action = IDLE;
		}
	}
	if (frm_mv.x != 0)
	{
		e->movement.x = frm_mv.x * MV_DUR;
		if (frm_mv.x > 0)
			e->flip_x = 0;
		else
			e->flip_x = 1;
	}
	if (frm_mv.y != 0)
		e->movement.y = frm_mv.y * MV_DUR;
	if ((frm_mv.x == 0 && frm_mv.y == 0))
	{
		e->cur_frame = e->idl_frm[e->cur_frame_index];
		e->cur_frame_x = e->idl_frm_x[e->cur_frame_index];
		e->action = IDLE;
	}
	else
	{
		e->cur_frame = e->wlk_frm[e->cur_frame_index];
		e->cur_frame_x = e->wlk_frm_x[e->cur_frame_index];
		e->action = WALK;
	}
	if (mlx->time % ANIM_REFRESH == 0)
	{
		e->cur_frame_index++;
		if (e->cur_frame_index > e->idle_frame_amount - 1)
			e->cur_frame_index = 0;
	}
	handle_movement(mlx, e, speed_x, speed_y);
	return (1);
}

char *action_names[5] = {"WALK", "FALL", "IDLE", "JUMP"};

int update_game_mobs(t_mlx_data *mlx_data)
{
	t_Vec3	new_movement;
	int			i;

	i = -1;
	while (++i < MOB_AMOUNT)
	{
		set_Vec3(&new_movement, 0,0,0);
		if (rand() % 500 == 0)
			new_movement = rand_Vec3(-MV_DUR / 2, MV_DUR / 2);
		update_entity(&mlx_data->game_mobs[i], new_movement, MOBS_SPD, MOBS_SPD, mlx_data);
	}
	return (1);
}

int	update_player(t_mlx_data *mlx_data)
{
	int			move_speed[2];
	t_Vec3	new_mv;

	//printf("PLAYER: %s JMP_TIMER: %d\n", action_names[mlx_data->player.action], mlx_data->player.jump_timer);
	set_Vec3(&new_mv, 0,0,0);
	if (mlx_data->key_state[LEFT_KEY] || mlx_data->key_state[A_KEY])
		new_mv.x = -1;
	else if (mlx_data->key_state[RIGHT_KEY] || mlx_data->key_state[D_KEY])
		new_mv.x = 1;
	else if (mlx_data->key_state[DOWN_KEY] || mlx_data->key_state[S_KEY])
		new_mv.y = 1;
	if (mlx_data->key_state[SPACE_KEY] && mlx_data->player.jump_timer == 0 && mlx_data->player.action != FALL)
	{
		mlx_data->player.jump_timer = 30;
		new_mv.y = -2;
	}
	if (mlx_data->key_state[SHIFT_KEY])
		move_speed[0] = PLAYER_SPEED * 3;
	else
		move_speed[0] = PLAYER_SPEED;
	move_speed[1] = PLAYER_SPEED;
	return (update_entity(&mlx_data->player, new_mv, move_speed[0], move_speed[1], mlx_data));
}

int	update(t_mlx_data *mlx_data)
{
	update_player(mlx_data);
	update_game_mobs(mlx_data);
	return (1);
}
