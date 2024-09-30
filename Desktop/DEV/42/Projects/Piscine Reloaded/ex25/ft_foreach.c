/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:59:23 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 11:19:24 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	i = 0;
	while (i < length)
	{
		f(tab[i++]);
	}
}

/*
#include <stdio.h>
#include <stdlib.h>
void    ft_putnbr(int nbr)
{
    printf("%d\n", nbr);
}
void    ft_putnbr_mult(int nbr)
{
    printf("%d\n", nbr*100);
}
int     main()
{
    int *arr = malloc(11 * sizeof(int));
    for (int  x = 0; x < 11; x++)
        arr[x] = x;
    ft_foreach(arr, 11, &ft_putnbr);
}*/