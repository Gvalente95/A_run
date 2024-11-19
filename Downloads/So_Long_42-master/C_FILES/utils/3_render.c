/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:01:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/19 04:21:39 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

void	render_text(t_md *md, t_vec2 pos, const char *format, ...)
{
	char	buff[256];
	int		of;
	va_list	args;

	va_start(args, format);
	vsnprintf(buff, sizeof(buff), format, args);
	va_end(args);
	of = 1;
	mlx_string_put(md->mlx, md->win, pos.x - of, pos.y - of, COLOR_BLACK, buff);
	mlx_string_put(md->mlx, md->win, pos.x + of, pos.y - of, COLOR_BLACK, buff);
	mlx_string_put(md->mlx, md->win, pos.x - of, pos.y + of, COLOR_BLACK, buff);
	mlx_string_put(md->mlx, md->win, pos.x + of, pos.y + of, COLOR_BLACK, buff);
	mlx_string_put(md->mlx, md->win, pos.x, pos.y, COLOR_YELLOW, buff);
}

void	*flip_image_x(void *mlx, void *img, t_vec2 size)
{
	t_vec2	pos;
	int		prm[5];
	void	*flipped_img;
	char	*src_data;
	char	*dest_data;

	flipped_img = mlx_new_image(mlx, size.x, size.y);
	if (!flipped_img)
		return (NULL);
	src_data = mlx_get_data_addr(img, &prm[0], &prm[1], &prm[2]);
	dest_data = mlx_get_data_addr(flipped_img, &prm[0], &prm[1], &prm[2]);
	if (!src_data || !dest_data)
		return (NULL);
	pos.y = -1;
	while (++pos.y < size.y)
	{
		pos.x = -1;
		while (++pos.x < size.x)
		{
			prm[3] = pos.y * prm[1] + (size.x - pos.x - 1) * (prm[0] / 8);
			prm[4] = pos.y * prm[1] + pos.x * (prm[0] / 8);
			ft_memcpy(dest_data + prm[4], src_data + prm[3], prm[0] / 8);
		}
	}
	return (flipped_img);
}

void	render_player(t_md *md)
{
	t_ent	*plr;
	void	*copy;

	plr = &md->plr;
	copy = plr->cur_frame;
	if (plr->flip_x)
		copy = flip_image_x(md, copy, plr->size);
	mlx_put_image_to_window(md->mlx, md->win, \
		copy, plr->pos.x, plr->pos.y);
}

void	render_array(t_md *md, t_ent **e, int len, int show_portal)
{
	int	i;

	(void)len;
	i = 0;
	while (e[i])
	{
		if (!show_portal && e[i]->type == portal)
		{
			i++;
			continue ;
		}
		if (e[i]->is_active && e[i]->cur_frame != NULL)
			mlx_put_image_to_window(md->mlx, md->win, \
			e[i]->cur_frame, e[i]->pos.x, e[i]->pos.y);
		i++;
	}
	if (!md->coins_amount && !show_portal)
	{
		mlx_put_image_to_window(md->mlx, md->win, \
		md->exit->cur_frame, md->exit->pos.x, md->exit->pos.y);
		if (abs(md->exit->pos.x - md->plr.pos.x) < md->exit->size.x / 2 && \
				abs(md->exit->pos.y - md->plr.pos.y) < md->exit->size.y / 2)
			exit(0);
	}
}

void	render(t_md *md)
{
	t_vec2	tx_p;

	mlx_put_image_to_window(md->mlx, md->win, \
	md->bg_col, 0, 0);
	if (md->bgrnd_img)
		mlx_put_image_to_window(md, md->win, \
			md->bgrnd_img, 0, 0);
	render_array(md, md->images, md->images_len, 0);
	set_vec2(&tx_p, md->t_len, md->t_len);
	render_text(md, get_vec2(md->plr.pos.x + md->plr.size.x / 2, \
		md->plr.pos.y - 5), "%d", md->move_counter);
	render_player(md);
}
