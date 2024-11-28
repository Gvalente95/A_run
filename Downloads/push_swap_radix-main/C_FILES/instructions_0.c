/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 02:34:36 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/28 15:15:03 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	parse_instruction_2(char *cmd, t_data *data)
{
	int	res;

	res = -1;
	if (!ft_strcmp(cmd, "rra"))
		res = (reverse_rotate(&data->pile_a));
	else if (!ft_strcmp(cmd, "rrb"))
		res = (reverse_rotate(&data->pile_b));
	else if (!ft_strcmp(cmd, "rrr"))
		res = (reverse_rotate(&data->pile_a) + reverse_rotate(&data->pile_b));
	else if (!ft_strcmp(cmd, "ra"))
		res = (rotate(&data->pile_a));
	else if (!ft_strcmp(cmd, "rb"))
		res = (rotate(&data->pile_b));
	else if (!ft_strcmp(cmd, "rr"))
		res = (rotate(&data->pile_a) + rotate(&data->pile_b));
	return (res);
}

int	parse_instruction_0(char *cmd, t_data *data)
{
	int	res;

	res = -1;
	if (!ft_strcmp(cmd, "sa"))
		res = swap(&data->pile_a);
	else if (!ft_strcmp(cmd, "sb"))
		res = swap(&data->pile_b);
	else if (!ft_strcmp(cmd, "ss"))
		res = swap(&data->pile_a) + swap(&data->pile_b);
	else if (!ft_strcmp(cmd, "pa"))
		res = put(&data->pile_a, &data->pile_b);
	else if (!ft_strcmp(cmd, "pb"))
		res = (put(&data->pile_b, &data->pile_a));
	else
		res = parse_instruction_2(cmd, data);
	return (res);
}

void	handle_visualizer(t_data *data)
{
	if (data->visualize == 1)
		print_piles_state(*data);
	if (data->visualize == 2)
	{
		system("clear");
		print_ranks(*data, 0, 0);
		while (getchar() != '\n')
			continue ;
	}
}

int	handle_instruction(char *cmd, t_data *data, int res)
{
	char	*prv;

	cmd = ft_strtrim(cmd, "\n");
	res = parse_instruction_0(cmd, data);
	if (res <= 0)
		return (res);
	if (data->cmd_len > 1)
	{
		prv = data->cmd_buff[data->cmd_len - 1];
		if (!ft_strcmp(prv, "ra") && !ft_strcmp(cmd, "rb"))
			ft_strlcpy(data->cmd_buff[data->cmd_len], "rr", 10);
		else if (!ft_strcmp(prv, "rb") && !ft_strcmp(cmd, "ra"))
			ft_strlcpy(data->cmd_buff[data->cmd_len], "rr", 10);
		else if (!ft_strcmp(prv, "rra") && !ft_strcmp(cmd, "rrb"))
			ft_strlcpy(data->cmd_buff[data->cmd_len], "rrr", 10);
		else if (!ft_strcmp(prv, "rrb") && !ft_strcmp(cmd, "rra"))
			ft_strlcpy(data->cmd_buff[data->cmd_len - 1], "rrr", 4);
		else
			data->cmd_buff[data->cmd_len++] = ft_strdup(cmd);
	}
	else
		data->cmd_buff[data->cmd_len++] = ft_strdup(cmd);
	handle_visualizer(data);
	return (res);
}

void	cp_element(t_element *to, t_element from)
{
	to->rank = from.rank;
	to->val = from.val;
}
