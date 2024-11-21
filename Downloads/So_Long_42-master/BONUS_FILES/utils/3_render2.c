/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_render2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 02:38:50 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 02:40:14 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

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
