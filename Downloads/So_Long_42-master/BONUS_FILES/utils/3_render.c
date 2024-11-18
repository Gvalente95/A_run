/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:01:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/18 16:05:21 by giuliovalen      ###   ########.fr       */
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

void	render_array(t_md *md, t_ent **e, int len)
{
	int	i;

	i = 0;
	sort_ents_by_z(md->images, len);
	while (e[i])
	{
		if (e[i]->type == portal)
		{
			if (md->coins_amount)
			{
				i++;
				continue ;
			}
			if (abs(e[i]->pos.x - md->plr.pos.x) < e[i]->size.x / 2 && \
				abs(e[i]->pos.y - md->plr.pos.y) < e[i]->size.y / 2)
				load_new_level(md);
		}
		if (e[i]->is_active && e[i]->cur_frame != NULL)
			mlx_put_image_to_window(md->mlx, md->win, \
			e[i]->cur_frame, e[i]->pos.x, e[i]->pos.y);
		i++;
	}
}

void	render_game_values(t_md *md)
{
	int		i;
	t_ent	*targ;
	t_vec2	pos;

	if (md->coins_amount == md->map.coin_max)
	{
		render_text(md, get_vec2(md->plr.pos.x + md->plr.size.x / 2, \
		md->plr.pos.y - md->plr.size.y / 2), "%d", 0);
		return ;
	}
	i = 0;
	while (i < md->images_len)
	{
		if (md->images[i]->type == coin && !md->images[i]->hp)
		{
			targ = md->images[i];
			set_vec2(&pos, targ->pos.x + targ->size.x / 2, \
			targ->pos.y - targ->size.y * 2);
			render_text(md, pos, "%d/%d", md->map.coins_amount \
					- md->coins_amount, md->map.coins_amount);
			break ;
		}
		i++;
	}
}

// render_text(md, get_vec2(tx_p.x, tx_p.y + md->t_len / 3), \
//	"DIM[x%d,y%d]", \
// 	md->map.size.x, md->map.size.y);
// render_text(md, get_vec2(tx_p.x, tx_p.y + (md->t_len / 3) * 2), \
//	"PLR hp%d");
// render_text(md, get_vec2(tx_p.x, tx_p.y + (md->t_len / 3) * 3), \
// "Pos[x%d,y%d]", md->plr.pos.x, md->plr.pos.y);
// render_text(md, get_vec2(tx_p.x, tx_p.y + (md->t_len / 3) * 4), \
// "Mov[x%d,y%d]", md->plr.movement.x, md->plr.movement.y);
// render_text(md, get_vec2(tx_p.x, tx_p.y + (md->t_len / 3) * 5), \
// "MOUSE[click%d,press%d]", md->mouse_clicked, md->mouse_pressed);
void	render(t_md *md)
{
	t_vec2	tx_p;

	mlx_put_image_to_window(md->mlx, md->win, \
	md->bg_col, 0, 0);
	if (md->bgrnd_img)
		mlx_put_image_to_window(md, md->win, \
			md->bgrnd_img, 0, 0);
	render_array(md, md->images, md->images_len);
	set_vec2(&tx_p, md->t_len, md->t_len);
	render_text(md, tx_p, "Move_count %d", md->move_counter);
	render_game_values(md);
	render_player(md);
	render_array(md, md->bg_env, md->bg_env_len);
}
