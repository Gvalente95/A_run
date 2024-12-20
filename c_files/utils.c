/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:50:16 by gvalente          #+#    #+#             */
/*   Updated: 2024/12/04 20:18:34 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <time.h>

int	is_in_val(t_pile pile, int val)
{
	int	i;

	i = 0;
	if (pile.size <= 0)
		return (0);
	while (i < pile.size)
	{
		if (pile.elements[i].val == val)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	is_sorted(t_data data)
{
	int	i;

	if (data.pile_b.size)
		return (0);
	i = data.pile_a.size - 1;
	while (i > 0)
	{
		if (data.pile_a.elements[i - 1].val < data.pile_a.elements[i].val)
			return (0);
		i--;
	}
	return (1);
}

int	free_data(t_data *data)
{
	if (data->pile_a.elements)
		free(data->pile_a.elements);
	if (data->pile_b.elements)
		free(data->pile_b.elements);
	if (data->cmd_len)
	{
		while (data->cmd_len)
		{
			if (data->cmd_buff[data->cmd_len - 1])
				free(data->cmd_buff[data->cmd_len - 1]);
			data->cmd_len--;
		}
		free(data->cmd_buff);
	}
	return (1);
}

void	print_ranks(t_data data, int wait_time, int i)
{
	int	max_len;

	max_len = data.pile_a.size;
	if (data.pile_b.size > data.pile_a.size)
		max_len = data.pile_b.size;
	i = 0;
	ft_printf("\n_______\n\n");
	while (i < max_len)
	{
		if (data.pile_a.size > 0 && i < data.pile_a.size)
			ft_printf("i%-3d r%-5d", i, data.pile_a.elements[i].rank);
		else
			ft_printf("           ");
		if (data.pile_b.size > 0 && i < data.pile_b.size)
			ft_printf("i%-3d r%d", i, data.pile_b.elements[i].rank);
		else
			ft_printf("           ");
		ft_printf("\n");
		i++;
	}
	ft_printf("-              -\na     b\n");
	ft_printf("%-10d%d\n\n", data.pile_a.size, data.pile_b.size);
	usleep(wait_time);
}
