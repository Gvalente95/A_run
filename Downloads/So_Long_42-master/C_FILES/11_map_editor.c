/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_map_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:00:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/11 12:57:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void set_new_category(t_mlx_data *mlx_data, int new_cat, int cur_index)
{
	if (mlx_data->alll_images[new_cat][cur_index])
		mlx_data->selected = mlx_data->alll_images[new_cat][cur_index];
	else if (mlx_data->alll_images[new_cat])
		mlx_data->selected = mlx_data->alll_images[new_cat][0];
	set_ent_to_mouse(mlx_data->selected, mlx_data);
}

void handle_inputs(t_mlx_data *mlx_data)
{
	static t_vec2 sel_size = {0};
	static t_ent *sel = NULL;
	static int	cur_index = 0;

	if (!(mlx_data->key_state[SPACE_KEY] && sel))
		sel = get_at_pos(get_Vec3(mlx_data->mouse_pos[0], mlx_data->mouse_pos[1], 0), get_Vec2(1,1), mlx_data->images, mlx_data->images_len);
	if (sel != NULL && !sel->cur_frame)
	{
		sel->cur_frame = add_img(sel->frame_path, &sel_size.x, &sel_size.y, mlx_data);
		sel->cur_frame = rescale_image(mlx_data, sel->cur_frame, &sel->size.x, &sel->size.y, sel->size.x, sel->size.y);
		set_img_color(sel->size, sel->cur_frame, COLOR_BLUE, .8);
	}
	if (sel)
	{
		mlx_put_image_to_window(mlx_data, mlx_data->win, sel->cur_frame, sel->pos.x - 5, sel->pos.y - 5);
		if (mlx_data->last_key_pressed == C_KEY)
			mlx_data->selected = copy_ent(sel);
		if (mlx_data->key_state[SPACE_KEY])
			set_ent_to_mouse(sel, mlx_data);
	}
	if (mlx_data->mouse_button == MOUSE_DPRESS)
		delete_ents_at_pos(get_Vec3(mlx_data->mouse_pos[0], mlx_data->mouse_pos[1], 0), get_Vec2(1, 1), mlx_data->images, &mlx_data->images_len);
	else if (mlx_data->clicked && mlx_data->mouse_prv != MOUSE_DPRESS)
	{
		if (mlx_data->selected->type == background)
			mlx_data->background = copy_ent(mlx_data->selected);
		else
		{
			mlx_data->images[mlx_data->images_len] = copy_ent(mlx_data->selected);
			mlx_data->images_len++;
			sort_game_entities_by_z_pos(mlx_data->images, mlx_data->images_len);
		}
	}
	if (mlx_data->mouse_button == 4)
	{
		cur_index--;
		if (cur_index < 0)
			cur_index = 0;
		mlx_data->selected = mlx_data->alll_images[mlx_data->cur_category][cur_index];
		set_ent_to_mouse(mlx_data->selected, mlx_data);
	}
	else if (mlx_data->mouse_button == 5)
	{
		cur_index++;
		if (!mlx_data->alll_images[mlx_data->cur_category][cur_index])
			cur_index = 0;
		mlx_data->selected = mlx_data->alll_images[mlx_data->cur_category][cur_index];
		set_ent_to_mouse(mlx_data->selected, mlx_data);
	}
	else if (mlx_data->last_key_pressed == W_KEY)
	{
		mlx_data->selected->pos.z++;
		//set_brightness(mlx_data->selected->size.x, mlx_data->selected->size.y, mlx_data->selected->cur_frame, 1 - (mlx_data->selected->pos.z / 10));	
	}
	else if (mlx_data->last_key_pressed == X_KEY)
		mlx_data->selected->pos.z--;
	else if (mlx_data->last_key_pressed == A_KEY && mlx_data->cur_category > 0)
		set_new_category(mlx_data, --mlx_data->cur_category, cur_index);
	else if (mlx_data->last_key_pressed == D_KEY && 
    mlx_data->cur_category < CAT_COUNT - 1 && 
    mlx_data->alll_images[mlx_data->cur_category + 1])
		set_new_category(mlx_data, ++mlx_data->cur_category, cur_index);
	else if (mlx_data->last_key_pressed == S_KEY && mlx_data->images_len > 0)
		save_to_file(mlx_data, mlx_data->images_len);
}

void check_test_img(t_mlx_data *mlx_data)
{
	static void *frame;
	static t_vec2 size = {0};
	if (mlx_data->time % 50 == 0)
	{
		void *image = add_img("RESSOURCES/PNG/BUSH/0.png", &size.x, &size.y, mlx_data);
		if (image)
		{
			set_brightness(50, 50, image, 1 / 10);
			mlx_put_image_to_window(mlx_data, mlx_data->win, image, 200, 200);
			frame = get_image_copy(mlx_data, image,size);			
		}
		if (frame != NULL)
		{
			mlx_put_image_to_window(mlx_data, mlx_data->win, frame, 50, 50);
		}
	}
}

int	update_and_render(t_mlx_data *mlx_data)
{
	update_mouse(mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	mlx_data->background_color, 0, 0);
	render_map_images(mlx_data);
	set_ent_to_mouse(mlx_data->selected, mlx_data);
	handle_inputs(mlx_data);
	reset_mlx_values(mlx_data);
	mlx_data->time++;

	//check_test_img(mlx_data);
	

	return (0);
}

int main(int argc, char **argv)
{
	t_mlx_data	mlx_data;

	mlx_data.images = calloc(500, sizeof(t_ent *));
	mlx_data.time = 0;
	srand(time(0));
	if (!init_mlx_data(&mlx_data, get_Vec2(WIN_W, WIN_H)))
		return (1);
	load_images(&mlx_data);
	mlx_data.selected = mlx_data.alll_images[0][0];
	init_mouse(&mlx_data);
	if (argc == 2)
		load_from_file(&mlx_data, argv[1]);
	mlx_hook(mlx_data.win, KEY_PRESS, 0, handle_key_press, &mlx_data);
	mlx_hook(mlx_data.win, KEY_RELEASE, 0, handle_key_release, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, (int (*)())update_and_render, &mlx_data);
	mlx_loop(mlx_data.mlx);
	return (0);
}