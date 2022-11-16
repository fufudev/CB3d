/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnljoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:26:39 by ffiliz            #+#    #+#             */
/*   Updated: 2022/01/25 19:26:55 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnljoin(char *s1, char *s2)
{
	char	*pt;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	i = 0;
	j = 0;
	pt = (char *)malloc (sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (pt == NULL)
		return (NULL);
	while (s1[i])
	{
		pt[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		pt[i + j] = s2[j];
		j++;
	}
	pt[i + j] = '\0';
	free(s1);
	return (pt);
}
