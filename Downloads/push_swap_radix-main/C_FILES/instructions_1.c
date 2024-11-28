/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:06:59 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/28 01:55:16 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	swap_entities(t_element *a, t_element *b)
{
	t_element	tmp;

	tmp.val = a->val;
	tmp.rank = a->rank;
	a->val = b->val;
	a->rank = b->rank;
	b->val = tmp.val;
	b->rank = tmp.rank;
}

int	swap(t_pile *pile)
{
	if (pile->size <= 1)
		return (0);
	swap_entities(&pile->elements[pile->size - 1], \
		&pile->elements[pile->size - 2]);
	return (1);
}

int	put(t_pile *receiver, t_pile *giver)
{
	if (giver->size <= 0)
		return (0);
	receiver->size++;
	cp_element(&receiver->elements[receiver->size - 1], \
		giver->elements[giver->size - 1]);
	giver->size--;
	return (1);
}

int	rotate(t_pile *pile)
{
	int			i;
	t_element	tmp;

	if (pile->size <= 1)
		return (0);
	cp_element(&tmp, pile->elements[pile->size - 1]);
	i = pile->size - 1;
	while (i > 0)
	{
		cp_element(&pile->elements[i], pile->elements[i - 1]);
		i--;
	}
	cp_element(&pile->elements[0], tmp);
	return (1);
}

int	reverse_rotate(t_pile *pile)
{
	int			i;
	t_element	tmp;

	if (pile->size <= 1)
		return (0);
	cp_element(&tmp, pile->elements[0]);
	i = 0;
	while (i < pile->size -1)
	{
		cp_element(&pile->elements[i], pile->elements[i + 1]);
		i++;
	}
	cp_element(&pile->elements[pile->size - 1], tmp);
	return (1);
}
