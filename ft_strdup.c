/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:59:14 by pabromer          #+#    #+#             */
/*   Updated: 2024/04/12 12:59:39 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	count;
	char	*dest;

	count = ft_strlen(s1) + 1;
	dest = (char *)malloc(count);
	if (dest)
	{
		dest = (char *) ft_memcpy(dest, s1, count);
	}
	else
		return (NULL);
	return (dest);
}
