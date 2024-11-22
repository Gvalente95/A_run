/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_load_editor_images.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:57:04 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/22 01:53:03 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_ent	*set_new_image(t_md *md, t_ent_type type, char *path, t_vec2 size)
{
	t_ent	*e;

	e = malloc(sizeof(t_ent));
	if (!e)
		return (NULL);
	set_vec3(&e->pos, 0, 0, 0);
	e->anim_frames = NULL;
	e->cur_frame = mlx_png_file_to_image(md, path, &e->size.x, &e->size.y);
	e->cur_frame = scale_img(md, e->cur_frame, &e->size, size);
	e->type = type;
	set_vec3(&e->pos, 0, 0, 0);
	return (e);
}

t_ent	*get_image_from_file(t_md *md, t_ent_type type, char *path)
{
	t_ent	*e;
	char	*final_path;

	e = malloc(sizeof(t_ent));
	final_path = ft_strjoin(path, "0.png");
	e = set_new_image(md, type, final_path, get_vec2(md->t_len, md->t_len));
	if (!e)
		return (NULL);
	free(final_path);
	return (e);
}

void	load_images(t_md *md)
{
	md->all_images = malloc(sizeof(t_ent *) * 8);
	if (!md->all_images)
		return ;
	md->all_images[0] = get_image_from_file(md, player, PLAYER_SPR_PATH);
	md->all_images[1] = get_image_from_file(md, mob, MOB_SPR_PATH);
	md->all_images[2] = get_image_from_file(md, coin, COIN_SPR_PATH);
	md->all_images[3] = get_image_from_file(md, key, KEY_SPR_PATH);
	md->all_images[4] = get_image_from_file(md, door, DOOR_SPR_PATH);
	md->all_images[5] = get_image_from_file(md, portal, PORTAL_SPR_PATH);
	md->all_images[6] = get_image_from_file(md, wall, WALL_SPR_PATH);
	md->all_images[7] = get_image_from_file(md, axe, AXE_SPR_PATH);
	md->all_images[8] = NULL;
	md->cur_category = 0;
}
