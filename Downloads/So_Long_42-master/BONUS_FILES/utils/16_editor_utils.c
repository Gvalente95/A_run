/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_editor_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:57:04 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 02:46:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

t_vec3	set_env_pos(t_md *md, t_vec2 size)
{
	t_vec3	pos;
	int		grid_x;
	int		grid_y;

	grid_x = r_range(1, md->map.size.x - 1) * md->t_len;
	grid_y = ((md->map.size.y) * (md->t_len - 1)) - md->t_len - \
		size.y + md->t_len / 3;
	grid_x += r_range(-md->t_len / 4, md->t_len / 4);
	if (grid_x < 0)
		grid_x = 0;
	if (grid_x > md->map.size.x * md->t_len - md->t_len)
		grid_x = md->map.size.x * md->t_len - md->t_len;
	if (grid_y < 0)
		grid_y = 0;
	if (grid_y > md->map.size.y * md->t_len - md->t_len)
		grid_y = md->map.size.y * md->t_len - md->t_len;
	set_vec3(&pos, grid_x, grid_y, 1);
	return (pos);
}

char	*get_random_path(void)
{
	char	*choosen_path;
	char	paths[3][100];

	ft_strlcpy(paths[0], BUSH_SPR_PATH, 100);
	ft_strlcpy(paths[1], TREES_SPR_PATH, 100);
	ft_strlcpy(paths[2], ROAD_SPR_PATH, 100);
	choosen_path = ft_strdup(paths[r_range(0, 2)]);
	return (choosen_path);
}

void	set_ent_image(t_ent *e, t_md *md, char *path, int i)
{
	char	*nbr;
	char	*full_path;
	float	aspect_ratio;
	t_vec2	size;

	nbr = ft_strjoin(ft_itoa(i), ".png");
	if (!nbr)
		return ;
	full_path = ft_strjoin(path, nbr);
	free(nbr);
	if (!full_path)
		return ;
	e->cur_frame = mlx_png_file_to_image(md, full_path, &e->size.x, &e->size.y);
	aspect_ratio = (float)e->size.x / (float)e->size.y;
	size.x = md->t_len - md->t_len / 10 + r_range(-md->t_len / \
		5, md->t_len / 5);
	if (!strncmp(path, "PNG/TREES", 9))
		size = get_vec2(size.x * 2, size.y * 2);
	size.y = size.x / aspect_ratio;
	e->cur_frame = scale_img(md, e->cur_frame, &e->size, size);
	free(full_path);
}

t_ent	*load_tree(t_md *md)
{
	char	*path;
	t_ent	*e;

	e = malloc(sizeof(t_ent));
	path = get_random_path();
	set_ent_image(e, md, path, r_range(0, 5));
	free(path);
	e->hp = 1;
	e->type = env;
	e->pos = set_env_pos(md, e->size);
	e->flip_x = 0;
	e->is_active = 1;
	return (e);
}

void	load_env_elements(t_md *md)
{
	int	i;

	md->bg_env_len = md->map.size.x / 2;
	md->bg_env = malloc(sizeof(t_ent *) * (md->bg_env_len + 1));
	if (!md->bg_env)
		return ;
	i = 0;
	while (i < md->bg_env_len)
	{
		md->bg_env[i] = load_tree(md);
		i++;
	}
	md->bg_env_len = i;
	md->bg_env[i] = NULL;
}
