/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:52:06 by pabromer          #+#    #+#             */
/*   Updated: 2024/05/14 11:07:43 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	char	b;
	long	a;
	size_t	i;

	i = 0;
	a = (long) n;
	if (a < 0)
	{
		write (1, "-", 1);
		a = -a;
		i++;
	}
	if (a < 10)
	{
		b = a + 48;
		i += ft_putchar(b);
	}
	else
	{
		i += ft_putnbr(a / 10);
		i += ft_putnbr(a % 10);
	}
	return (i);
}
