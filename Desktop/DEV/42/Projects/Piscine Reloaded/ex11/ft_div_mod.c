/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:31:55 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/13 17:36:05 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = (a / b);
	*mod = (a % b);
}
/*
#include <stdio.h>
int main()
{
	int a = 42, b = 8, div = 0, mod=0;
	printf("%d	%d\n", a,b);
	ft_div_mod(a,b,&div,&mod);
	printf("div:%d	mod:%d", div, mod); 
}*/
