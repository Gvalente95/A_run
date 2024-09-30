/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:34:33 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 13:05:11 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
#include <stdio.h>
int main()
{
	printf("%s\n%s\n%d\n\n", 
	"1234 2", "1234 3", ft_strcmp("1234 2", "1234 3"));
	printf("%s\n%s\n%d\n\n", 
	"hello2", "hello1", ft_strcmp("hello2", "hello1"));
	printf("%s\n%s\n%d\n\n", 
	"coucou", "coucou", ft_strcmp("coucou", "coucou"));
}*/
