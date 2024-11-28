/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:55:11 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/28 15:12:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <limits.h>
# include "libft/libft.h"

# define READ_BUFFER_SIZE 	5000

typedef struct s_element
{
	int		val;
	int		rank;
	int		processed;
}	t_element;

typedef struct s_pile
{
	int			size;
	t_element	*elements;
}	t_pile;

typedef struct s_data
{
	int		visualize;
	int		cmd_len;
	char	**cmd_buff;
	char	*algo_name;
	t_pile	pile_a;
	t_pile	pile_b;
}	t_data;

//		INSTRUCTIONS
int		handle_instruction(char *instruction, t_data *data, int res);
void	swap_entities(t_element *a, t_element *b);
void	cp_element(t_element *to, t_element from);
int		put(t_pile *receiver, t_pile *giver);
int		rotate(t_pile *pile);
int		reverse_rotate(t_pile *pile);
int		swap(t_pile *pile);

//		ALGORITHMS
int		radix_sort(t_data *data, int max_len, int digit_pos, int processed);
int		selection_sort(t_data *data, int operations, int direction, int i);
int		mini_sort(t_data *d, int size, int i, int res);
int		sort_five_in_a(t_data *data);
int		sort_four_in_a(t_data *data);
int		sort_three_in_a(t_data *data);
int		sort_three_in_b(t_data *data);
int		push_smallest_to_b(t_data *data);
int		push_smallest_to_a(t_data *data);
int		get_max_rank(t_pile pile);
int		*min_value(t_pile pile, int *values);
int		iterate_action(char *command, int len, t_data *data, t_pile *size);

//		UTILS
int		is_in_val(t_pile pile, int val);
long	ft_atol(const char *str);
int		is_sorted(t_data data);
int		free_data(t_data *data);
int		set_values_ranks(t_pile *pile, int i, int j, int cur_highest);
int		*max_value(t_pile pile, int *values);
char	*get_next_line(int fd);
void	print_ranks(t_data data, int wait_time, int i);

//		PRINT
void	print_commands(t_data *data);
void	print_vals(t_data data, int wait_time, int i);
void	print_and_quit(t_data *data);
void	print_piles_state(t_data d);

//		PARSING
int		arg_doublons_checker(t_data *data, char **arguments, int len);
int		is_contained(int value, int *values, int amount);
void	init_data(t_data *data, int argc, char *argv[], int visualize);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_printf(const char *format, ...);

#endif