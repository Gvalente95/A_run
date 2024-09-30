/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:19:44 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 11:44:07 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char*))
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (tab[i])
		res += f(tab[i++]);
	return (res);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ft_is_maj(char *txt) { return (txt[0] >= 'A' && txt[0] <= 'Z'); }
int ft_is_min(char *txt) { return (txt[0] >= 'a' && txt[0] <= 'z'); }

int     main()
{
	char **strings = (char**)malloc(sizeof(char*) * 11);
	strings[10] = NULL;
	for (int x = 0; x < 10; x++)
	{
		strings[x] = strdup(x % 3 == 0 ? "min" : "Maj");
		printf("%d : %s\n", x, strings[x]);
	}
	printf("min: %d\n", ft_count_if(strings, &ft_is_min));
	printf("Maj: %d", ft_count_if(strings, &ft_is_maj));
}*/