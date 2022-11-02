/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 21:12:23 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/10 16:17:33 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i++])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*pt;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (is_sep(s1[i], set))
		i++;
	if (i == len)
		return (ft_calloc(1, 1));
	while (is_sep(s1[--len], set))
		j++;
	len = ft_strlen(s1) - (i + j);
	pt = malloc(sizeof(char) * len + 1);
	if (!pt)
		return (NULL);
	pt[len] = '\0';
	j = 0;
	while (j < len)
		pt[j++] = s1[i++];
	return (pt);
}
