/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:06:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/28 15:18:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_vals(t_data data, int wait_time, int i)
{
	int	max_len;

	max_len = data.pile_a.size;
	if (data.pile_b.size > data.pile_a.size)
		max_len = data.pile_b.size;
	i = 0;
	while (i < max_len)
	{
		if (data.pile_a.size > 0 && i <= data.pile_a.size)
			ft_printf("%d      ", data.pile_a.elements[i].val);
		else
			ft_printf("       ");
		if (data.pile_b.size > 0 && i <= data.pile_b.size)
			ft_printf("%d      ", data.pile_b.elements[i].val);
		else
			ft_printf("       ");
		ft_printf("\n");
		i++;
	}
	ft_printf("-     -\na     b\n");
	ft_printf("%d    ", data.pile_a.size);
	ft_printf("%d\n\n", data.pile_b.size);
	usleep(wait_time);
}

void	print_and_quit(t_data *data)
{
	write(2, "Error\n", 6);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	print_commands(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->cmd_len)
	{
		ft_putstr_fd(data->cmd_buff[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	render_pile(t_pile pile, t_pile other_pile, int h, int i)
{
	int	j;
	int	max_rank;

	max_rank = get_max_rank(pile);
	j = -1;
	while (++j < pile.size)
	{
		if (j == 0)
			ft_printf("|");
		if (pile.elements[j].rank >= (i - 1) * (max_rank) / h)
			ft_printf("|");
		else
			ft_printf(" ");
	}
	j = -1;
	while (++j < pile.size + other_pile.size - pile.size)
		ft_printf(" ");
}

void	print_piles_state(t_data d)
{
	int	i;
	int	h;

	h = d.pile_a.size + d.pile_b.size;
	if (h > 20)
		h = 20;
	ft_printf("\n%s\n", d.algo_name);
	i = 0;
	while (i++ < (d.pile_a.size + d.pile_b.size + 1) * 2 + 1)
		ft_printf("_");
	ft_printf("\n");
	i = h;
	while (i > 0)
	{
		render_pile(d.pile_a, d.pile_b, h, i);
		render_pile(d.pile_b, d.pile_a, h, i);
		ft_printf("\n");
		i--;
	}
	while (i++ < (d.pile_a.size + d.pile_b.size + 1) * 2 + 1)
		ft_printf("_");
	ft_printf("\nGIULIO'S PUSH_SWAP VISUALIZER\n");
	usleep(100000 - (h * 4500));
	system("clear");
}
