/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:53:53 by pabromer          #+#    #+#             */
/*   Updated: 2024/04/18 10:53:56 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	size_t	sizejoin;

	if (!s1 || !s2)
		return (NULL);
	sizejoin = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(sizejoin);
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '\0';
	ft_strlcat(join, s2, sizejoin);
	return (join);
}
