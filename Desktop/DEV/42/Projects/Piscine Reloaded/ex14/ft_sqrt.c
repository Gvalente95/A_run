/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:09 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/13 18:26:48 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	nb_start;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	nb_start = (nb / 2) + 1;
	while (nb_start >= 1)
	{
		if (nb_start * nb_start == nb)
			return (nb_start);
		nb_start--;
	}
	return (0);
}

/*
#include <stdio.h>
#include <math.h>
int main()
{
for (int x = 0; x < 50; x++)
{
printf("%d : %d, math_res: %f\n",x, ft_sqrt(x), sqrt(x));
}
}*/
