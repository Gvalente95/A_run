/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_update_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:31:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 03:26:01 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	handle_mouse_press(t_ent *ent_at_mouse, t_md *md, t_vec2 lk_size)
{
	t_vec3	grd_p;
	t_ent	**tmp;

	if (md->mouse_clicked == MOUSE_PRESS || md->key_prs[SPACE_KEY])
	{
		if (ent_at_mouse)
			del_at_pos(md->mouse_pos, lk_size, md->images, &md->images_len);
		tmp = realloc(md->images, (md->images_len + 2) * \
		sizeof(t_ent *));
		if (!tmp)
		{
			ft_printf("realloc failed");
			return ;
		}
		md->images = tmp;
		md->images[md->images_len] = copy_ent(md->selected);
		md->images[md->images_len]->is_active = 1;
		grd_p = get_grid_pos(md, md->mouse_pos);
		md->images[md->images_len]->pos = grd_p;
		md->images[++md->images_len] = NULL;
	}
}

void	handle_keys(t_md *md, t_vec2 lk_size)
{
	if (md->key_prs[X_KEY])
		del_at_pos(md->mouse_pos, lk_size, md->images, &md->images_len);
	else if (md->key_clicked == A_KEY && md->index > 0)
		md->selected = md->all_images[--md->index];
	else if (md->key_clicked == D_KEY && md->index < 7)
		md->selected = md->all_images[++md->index];
	else if (md->key_clicked == S_KEY && md->images_len > 0 && md->images)
		md->save_mode = 1;
	else if (md->key_clicked == ENTER_KEY && md->map.name)
		relaunch_program(md->map.name);
}

void	handle_inputs(t_md *md, t_vec2 lk_size)
{
	t_ent	*ent_at_mouse;

	ent_at_mouse = get_at_pos(md->mouse_pos, lk_size, md->images, \
		md->images_len);
	handle_mouse_press(ent_at_mouse, md, lk_size);
	if (ent_at_mouse && !md->key_prs[X_KEY])
	{
		if (md->key_clicked == C_KEY || md->key_clicked == I_KEY)
			md->selected = copy_ent(ent_at_mouse);
	}
	handle_keys(md, lk_size);
}

int	update_editor(t_md *md)
{
	t_vec3	grid_pos;

	mlx_put_image_to_window(md->mlx, md->win, \
	md->bg_col, 0, 0);
	if (md->bgrnd_img)
		mlx_put_image_to_window(md, md->win, \
			md->bgrnd_img, 0, 0);
	md->coins_amount = 10;
	render_array(md, md->images, md->images_len, 1);
	if (md->selected && !md->key_prs[X_KEY] && !md->save_mode)
	{
		grid_pos = get_grid_pos(md, md->mouse_pos);
		mlx_put_image_to_window(md->mlx, md->win, md->selected->cur_frame, \
			grid_pos.x, grid_pos.y);
	}
	update_mouse(md);
	if (!md->save_mode)
		handle_inputs(md, get_vec2(1, 1));
	else
		save_to_file(md);
	reset_mlx_values(md);
	md->time++;
	return (0);
}
