/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_update_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:31:17 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 02:54:14 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	insert_entity(t_vec3 pos, t_ent *to_insert, t_ent ***arr, int *len)
{
	t_ent	**tmp;

	tmp = realloc(*arr, (*len + 2) * sizeof(t_ent *));
	if (!tmp)
	{
		ft_printf("realloc failed");
		return ;
	}
	*arr = tmp;
	(*arr)[*len] = copy_ent(to_insert);
	(*arr)[*len]->is_active = 1;
	(*arr)[*len]->pos = pos;
	(*arr)[++(*len)] = NULL;
}

void	handle_mouse_press(t_ent *ent_at_mouse, t_md *md, t_vec2 lk_size)
{
	if (ent_at_mouse)
	{
		if (md->key_clicked == C_KEY)
			md->index = ent_at_mouse->type;
		md->selected->pos.x += md->t_len / 2;
	}
	if (md->key_prs[SPACE_KEY] || md->mouse_clicked == MOUSE_PRESS)
	{
		if (ent_at_mouse && !md->key_prs[SHIFT_KEY])
			del_at_pos(md->mouse_pos, lk_size, md->images, &md->images_len);
		if (!ent_at_mouse || !md->key_prs[SHIFT_KEY])
			insert_entity(get_grid_pos(md, md->mouse_pos), md->selected, \
			&md->images, &md->images_len);
	}
	if (md->mouse_pressed == MOUSE_DPRESS || md->key_prs[X_KEY])
	{
		if (md->key_prs[SHIFT_KEY])
		{
			if (ent_at_mouse)
				md->index = ent_at_mouse->type;
			delete_type(md->index, md->images, &md->images_len);
		}
		else
			del_at_pos(md->mouse_pos, lk_size, md->images, &md->images_len);
	}
}

void	handle_keys(t_md *md)
{
	if (md->key_clicked == P_KEY)
		md->index = (int)player;
	else if (md->key_clicked == E_KEY)
		md->index = (int)portal;
	else if (md->key_clicked == W_KEY)
		md->index = (int)wall;
	else if (md->key_clicked == M_KEY)
		md->index = (int)mob;
	else if (md->key_clicked == K_KEY)
		md->index = (int)key;
	else if (md->key_clicked == I_KEY)
		md->index = (int)coin;
	else if (md->key_clicked == A_KEY && md->index > 0)
		md->selected = md->all_images[--md->index];
	else if (md->key_clicked == D_KEY && md->index < 7)
		md->selected = md->all_images[++md->index];
	else if (md->key_clicked == S_KEY && md->images_len > 0 && md->images)
		save_to_file(md);
	if (md->key_clicked)
		md->selected = md->all_images[md->index];
}

int	handle_inputs(t_md *md, t_vec2 lk_size)
{
	t_ent	*ent_at_mouse;

	ent_at_mouse = get_at_pos(md->mouse_pos, lk_size, md->images, \
		md->images_len);
	handle_mouse_press(ent_at_mouse, md, lk_size);
	handle_keys(md);
	if (md->key_clicked == ENTER_KEY && md->map.name)
		relaunch_program(md->map.name);
	return (ent_at_mouse != NULL);
}

int	update_editor(t_md *md)
{
	t_vec3	grid_pos;
	int		is_hover;

	is_hover = 0;
	if (md->bgrnd_img)
		mlx_put_image_to_window(md, md->win, \
			md->bgrnd_img, 0, 0);
	md->coins_amount = 10;
	sort_ents_by_z(md->images, md->images_len);
	render_array(md, md->images, 1, 0);
	update_mouse(md);
	is_hover = handle_inputs(md, get_vec2(1, 1));
	if (md->selected && !md->key_prs[X_KEY])
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
