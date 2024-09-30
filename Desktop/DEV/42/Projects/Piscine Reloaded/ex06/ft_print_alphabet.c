/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:55:43 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 12:56:32 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_print_alphabet(void)
{
	char	c;

	c = 'a';
	while (c != 'z')
	{
		write(1, &c, 1);
		c++;
	}
}

/*
int main()
{
ft_print_alphabet();
}
*/
