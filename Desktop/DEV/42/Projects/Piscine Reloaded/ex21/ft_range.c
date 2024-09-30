/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:30:15 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 01:58:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int		*res;
	int		cur;

	if (min >= max)
	{
		res = NULL;
		return (res);
	}
	cur = 0;
	res = malloc(max - min - 1);
	while (min < max)
		res[cur++] = min++;
	return (res);
}

/*
#include <stdio.h>
int main()
{
    int *i;
	int min = 4, max = 16;

	i = ft_range(min, max);
	for (int x = 0; x < max - min; x++)
	{
		printf("%d\n", i[x]);
	}
}
*/