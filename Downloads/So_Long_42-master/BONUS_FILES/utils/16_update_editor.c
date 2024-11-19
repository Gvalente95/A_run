/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_update_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:31:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 15:07:38 by giuliovalen      ###   ########.fr       */
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
	else if (md->key_clicked == P_KEY)
	{
		md->index = (int)player;
		md->selected = md->all_images[md->index];
	}
	else if (md->key_clicked == E_KEY)
	{
		md->index = (int)portal;
		md->selected = md->all_images[md->index];
	}
	else if (md->key_clicked == W_KEY)
	{
		md->index = (int)wall;
		md->selected = md->all_images[md->index];
	}
	else if (md->key_clicked == A_KEY && md->index > 0)
		md->selected = md->all_images[--md->index];
	else if (md->key_clicked == D_KEY && md->index < 7)
		md->selected = md->all_images[++md->index];
	else if (md->key_clicked == S_KEY && md->images_len > 0 && md->images)
		save_to_file(md);
	else if (md->key_clicked == ENTER_KEY && md->map.name)
		relaunch_program(md->map.name);
}

int	handle_inputs(t_md *md, t_vec2 lk_size)
{
	t_ent	*ent_at_mouse;

	ent_at_mouse = get_at_pos(md->mouse_pos, lk_size, md->images, \
		md->images_len);
	handle_mouse_press(ent_at_mouse, md, lk_size);
	if (ent_at_mouse && !md->key_prs[X_KEY])
	{
		if (md->key_clicked == C_KEY || md->key_clicked == I_KEY)
			md->selected = copy_ent(ent_at_mouse);
		md->selected->pos.x += 20;
	}
	handle_keys(md, lk_size);
	return (ent_at_mouse != NULL);
}

int	update_editor(t_md *md)
{
	t_vec3	grid_pos;
	int		is_hover;

	is_hover = 0;
	mlx_put_image_to_window(md->mlx, md->win, \
	md->bg_col, 0, 0);
	if (md->bgrnd_img)
		mlx_put_image_to_window(md, md->win, \
			md->bgrnd_img, 0, 0);
	md->coins_amount = 10;
	render_array(md, md->images, md->images_len, 1);
	update_mouse(md);
	is_hover = handle_inputs(md, get_vec2(1, 1));
	if (md->selected && !md->key_prs[X_KEY] && !md->save_mode)
	{
		grid_pos = get_grid_pos(md, md->mouse_pos);
		if (is_hover)
			grid_pos = get_vec3(grid_pos.x - md->t_len / 10, grid_pos.y - \
				md->t_len / 10, grid_pos.z);
		mlx_put_image_to_window(md->mlx, md->win, md->selected->cur_frame, \
			grid_pos.x, grid_pos.y);
	}
	reset_mlx_values(md);
	md->time++;
	return (0);
}
