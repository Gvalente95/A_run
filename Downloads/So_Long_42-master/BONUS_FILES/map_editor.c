/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:00:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 17:15:41 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	set_new_category(t_md *md, int new_cat, int cur_index)
{
	if (&md->all_images[new_cat][cur_index])
		md->selected = md->all_images[new_cat][cur_index];
	else if (md->all_images[new_cat])
		md->selected = md->all_images[new_cat][0];
	set_ent_to_mouse(md->selected, md);
}

void	handle_keys(t_md *md)
{
	if (md->mouse_clicked == MOUSE_SCROLL)
	{
		if (md->index > 0)
			md->index--;
		md->selected = md->all_images[md->cur_category][md->index];
		set_ent_to_mouse(md->selected, md);
	}
	if (md->key_clicked == W_KEY)
		md->selected->pos.z++;
	else if (md->key_clicked == X_KEY)
		md->selected->pos.z--;
	else if (md->key_clicked == A_KEY && md->cur_category > 0)
		set_new_category(md, --md->cur_category, md->index);
	else if (md->key_clicked == D_KEY && \
		md->cur_category < CAT_COUNT - 1 && \
			md->all_images[md->cur_category + 1])
		set_new_category(md, ++md->cur_category, md->index);
	// else if (md->key_clicked == S_KEY && md->images_len > 0)
	// 	save_to_file(md, md->images_len);
}

void	handle_inputs(t_md *md, t_vec3 mouse_pos, t_vec2 sel_size, t_ent *sel)
{
	if (!(md->key_prs[SPACE_KEY] && sel))
		sel = get_at_pos(mouse_pos, get_vec2(1, 1), md->images, md->images_len);
	if (sel != NULL && !sel->cur_frame)
	{
		sel->cur_frame = add_img(sel->frame_path, &sel_size.x, &sel_size.y, md);
		sel->cur_frame = scale_img(md, sel->cur_frame, &sel->size, sel_size);
		//set_img_color(sel->size, sel->cur_frame, COLOR_BLUE, .8);
	}
	if (sel)
	{
		mlx_put_image_to_window(md, md->win, sel->cur_frame, \
			sel->pos.x - 5, sel->pos.y - 5);
		if (md->key_clicked == C_KEY)
			md->selected = copy_ent(sel);
		if (md->key_prs[SPACE_KEY])
			set_ent_to_mouse(sel, md);
	}
	if (md->key_clicked == MOUSE_DPRESS)
		del_at_pos(mouse_pos, get_vec2(1, 1), md->images, &md->images_len);
	else if (md->key_clicked == MOUSE_PRESS)
		md->images[md->images_len++] = copy_ent(md->selected);
	handle_keys(md);
}

int	update_editor(t_md *md)
{
	update_mouse(md);
	mlx_put_image_to_window(md->mlx, md->win, \
	md->bg_col, 0, 0);
	render_array(md, md->images, md->images_len);
	set_ent_to_mouse(md->selected, md);
	handle_inputs(md, get_vec3(md->mouse_pos[0], md->mouse_pos[1], 1), \
		get_vec2(0, 0), md->sel);
	reset_mlx_values(md);
	md->time++;
	return (0);
}

int	main(int argc, char **argv)
{
	t_md			md;

	md.images = calloc(500, sizeof(t_ent *));
	md.time = 0;
	md.index = 0;
	md.sel = NULL;
	md.win = NULL;
	srand(time(0));
	init_mlx(&md);
	if (argc == 2)
		load_valid_map(argv[1], &md, NULL, get_vec2(0, 0));
	init_game(&md);
	load_images(&md);
	exit(0);
	md.selected = md.all_images[0][0];
	mlx_hook(md.win, KEY_PRESS, 0, handle_key_press, &md);
	mlx_hook(md.win, KEY_RELEASE, 0, handle_key_release, &md);
	mlx_loop_hook(md.mlx, (int (*)())update_editor, &md);
	mlx_loop(md.mlx);
	return (0);
}
