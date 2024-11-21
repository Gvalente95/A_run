/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_map_parser_editor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:42 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 19:48:58 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_ent	*init_map_entity(t_md *md, t_vec3 pos, t_ent_type type, t_ent *img)
{
	t_ent	*e;

	e = malloc(sizeof(t_ent));
	if (!e)
	{
		ft_printf("ALLOC FAILED");
		return (NULL);
	}
	e->anim_frames = NULL;
	e->fly_frm = NULL;
	e->wlk_frm = NULL;
	e->frame_path = NULL;
	e->idl_frm = NULL;
	e->size = get_vec2(md->t_len, md->t_len);
	e->pos = get_vec3(pos.x * md->t_len, pos.y * md->t_len, pos.z);
	e->is_active = 1;
	e->hp = 5;
	e->hurt_timer = 0;
	e->base_pos = e->pos;
	e->flip_x = 0;
	e->type = type;
	e->cur_frame = img->cur_frame;
	return (e);
}

t_ent	*parse_letter_editor(t_md *md, t_vec3 pos, char c)
{
	t_ent	*ent;

	ent = NULL;
	if (c == '1')
		ent = init_map_entity(md, pos, wall, md->all_images[(int)wall]);
	else if (c == 'E')
		ent = init_map_entity(md, pos, axe, md->all_images[(int)portal]);
	else if (c == 'T')
		ent = init_map_entity(md, pos, tile, md->all_images[(int)tile]);
	else if (c == 'D')
		ent = init_map_entity(md, pos, door, md->all_images[(int)door]);
	else if (c == 'C')
		ent = init_map_entity(md, pos, coin, md->all_images[(int)coin]);
	else if (c == 'M')
		ent = init_map_entity(md, pos, mob, md->all_images[(int)mob]);
	else if (c == 'P')
		ent = init_map_entity(md, pos, player, md->all_images[(int)player]);
	else if (c == 'K')
		ent = init_map_entity(md, pos, key, md->all_images[(int)key]);
	else if (c == 'A')
		ent = init_map_entity(md, pos, axe, md->all_images[(int)axe]);
	return (ent);
}

void	load_ents_editor(t_md *md, int i, t_vec3 pos)
{
	t_ent	*e;
	int		len;

	len = (md->map.size.x) * (md->map.size.y) + 1;
	md->images = malloc(sizeof(t_ent *) * len);
	i = 0;
	pos.y = 0;
	md->images_len = 0;
	while (pos.y < md->map.size.y)
	{
		pos.x = 0;
		while (pos.x < md->map.size.x)
		{
			e = parse_letter_editor(md, pos, md->map.buffer[i]);
			if (e)
				md->images[md->images_len++] = e;
			i++;
			pos.x++;
		}
		pos.y++;
		i++;
	}
	md->images[md->images_len] = NULL;
}

int	check_path_format(char *path)
{
	char	path_check[4];
	int		i;
	int		len;

	len = 0;
	i = ft_strlen(path) - 1;
	while (len < 4)
	{
		path_check[len] = path[i];
		len++;
		i--;
	}
	return (ft_strncmp(path_check, "reb.", 4));
}

char	*store_map_name(t_md *md)
{
	char	*x_size;
	char	*y_size;
	char	*size;
	char	*size_part_0;

	x_size = ft_itoa(md->map.size.x);
	y_size = ft_itoa(md->map.size.y);
	size_part_0 = ft_strjoin(x_size, "x");
	size = ft_strjoin(size_part_0, y_size);
	free(x_size);
	free(y_size);
	free(size_part_0);
	return (size);
}
