/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:52:06 by pabromer          #+#    #+#             */
/*   Updated: 2024/05/14 11:10:18 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int n)
{
	char	b;
	size_t	i;

	i = 0;
	if (n < 10)
	{
		b = n + 48;
		i += ft_putchar(b);
	}
	else
	{
		i += ft_putunbr(n / 10);
		i += ft_putunbr(n % 10);
	}
	return (i);
}
