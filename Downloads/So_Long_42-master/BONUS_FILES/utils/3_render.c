/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:01:26 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/21 23:32:16 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/header.h"

void	render_player(t_md *md)
{
	t_ent	*plr;
	void	*copy;

	plr = &md->plr;
	if (plr->hurt_timer)
	{
		plr->hurt_timer--;
		if ((md->time / 10) % 2 == 0)
			return ;
	}
	copy = plr->cur_frame;
	if (plr->flip_x)
		copy = flip_image_x(md, copy, plr->size);
	mlx_put_image_to_window(md->mlx, md->win, \
		copy, plr->pos.x, plr->pos.y);
}

void	render_array(t_md *md, t_ent **e, int show_portal, int i)
{
	t_vec2	offs;

	while (e[i])
	{
		offs = get_vec2(0, 0);
		if (e[i]->type == portal && !show_portal)
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
		{
			if (e[i]->hurt_timer)
				offs = get_vec2(r_range(-5, 5), r_range(-5, 5));
			mlx_put_image_to_window(md->mlx, md->win, e[i]->cur_frame, \
				e[i]->pos.x + offs.x, e[i]->pos.y + offs.y);
		}
		i++;
	}
}

void	render_particles(t_md *md)
{
	int	i;

	if (!md->particles || !md->particles_alive)
		return ;
	i = 0;
	while (md->particles[i] && i < md->particles_alive && i < PRT_AMOUNT)
	{
		if (md->particles[i]->is_active)
			mlx_put_image_to_window(md, md->win, md->particles[i]->cur_frame, \
				md->particles[i]->pos.x, md->particles[i]->pos.y);
		i++;
	}
}

void	render(t_md *md)
{
	int		i;
	t_vec2	tx_p;

	if (md->bgrnd_img)
		mlx_put_image_to_window(md, md->win, \
			md->bgrnd_img, md->t_len, md->t_len);
	i = -1;
	while (++i < md->bg_env_len / 2)
		mlx_put_image_to_window(md, md->win, md->bg_env[i]->cur_frame, \
			md->bg_env[i]->pos.x, md->bg_env[i]->pos.y);
	sort_ents_by_z(md->images, md->images_len);
	render_array(md, md->images, 0, 0);
	set_vec2(&tx_p, md->t_len, md->t_len);
	render_text(md, tx_p, "Move_count %d", md->move_counter);
	render_game_values(md);
	render_player(md);
	while (++i < md->bg_env_len)
		mlx_put_image_to_window(md, md->win, md->bg_env[i]->cur_frame, \
			md->bg_env[i]->pos.x, md->bg_env[i]->pos.y);
	render_particles(md);
}
