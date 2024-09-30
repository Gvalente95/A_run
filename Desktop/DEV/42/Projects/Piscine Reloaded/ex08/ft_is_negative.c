/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:09:03 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/13 17:28:15 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int n)
{
	if (n < 0)
		write(1, "N", 1);
	else
		write(1, "P", 1);
}

/*
#include <stdio.h>
int main()
{
int a = 1;
int b = -5;

printf(" for %d", a);
ft_is_negative(a);
printf("\n for %d", b);
ft_is_negative(b);
}*/
