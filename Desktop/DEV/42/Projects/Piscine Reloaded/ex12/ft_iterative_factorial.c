/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:36:29 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/13 18:00:45 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	result;
	int	cur_nbr;

	if (nb <= 0)
		return (0);
	result = 1;
	cur_nbr = nb;
	while (cur_nbr > 1)
	{
		result *= cur_nbr;
		cur_nbr--;
	}
	return (result);
}

/*
#include <stdio.h>
int main()
{
	for (int x = 0; x < 10; x++)
		printf("%d : %d\n",x, ft_iterative_factorial(x));
}*/
