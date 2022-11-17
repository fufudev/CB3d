/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:18:39 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/10 16:14:35 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned int	i;
	char			*pt;

	i = 0;
	if (!f || !s)
		return (NULL);
	pt = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (pt == NULL)
		return (NULL);
	while (s[i])
	{
		pt[i] = (*f)(i, s[i]);
		i++;
	}
	pt[i] = '\0';
	return (pt);
}
