/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:44:43 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/27 22:07:55 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr(unsigned long addr)
{
	int	len;

	len = 0;
	len += ft_putstr("0x");
	len += ft_puthex(addr, 'x');
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_puthex(unsigned long nbr, char c)
{
	int	len;

	len = 0;
	if (nbr > 15)
		len += ft_puthex(nbr / 16, c);
	if (c == 'x')
		len += write(1, &"0123456789abcdef"[nbr % 16], 1);
	else
		len += write(1, &"0123456789ABCDEF"[nbr % 16], 1);
	return (len);
}

int	ft_putunbr(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr > 9)
		len += ft_putunbr(nbr / 10);
	len += ft_putchar(nbr % 10 + '0');
	return (len);
}

int	ft_putnbr(int nb)
{
	long	nbr;
	int		len;

	len = 0;
	nbr = nb;
	if (nbr < 0)
	{
		len += ft_putchar('-');
		nbr = nbr * -1;
	}
	if (nbr > 9)
		len += ft_putnbr(nbr / 10);
	len += ft_putchar(nbr % 10 + '0');
	return (len);
}
