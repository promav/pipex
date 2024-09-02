/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:52:06 by pabromer          #+#    #+#             */
/*   Updated: 2024/05/14 11:06:03 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(unsigned long long n, char c)
{
	unsigned long long	i;

	i = 0;
	if (n >= 16)
		i += ft_puthexa(n / 16, c);
	if (c == 'x')
		ft_putchar("0123456789abcdef"[n % 16]);
	if (c == 'X')
		ft_putchar("0123456789ABCDEF"[n % 16]);
	i++;
	return (i);
}
