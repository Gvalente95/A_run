/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:30:03 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 01:38:50 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*dst;
	int		len;

	if (src == NULL)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	dst = malloc(len - 1);
	len = 0;
	while (src[len])
	{
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return (dst);
}

/*
#include <stdio.h>
int main()
{
    char *newTxt = ft_strdup("\0");
    printf("%s", newTxt);
}*/