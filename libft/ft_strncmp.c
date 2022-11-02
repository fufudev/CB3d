/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnmcp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:30:55 by ffiliz            #+#    #+#             */
/*   Updated: 2021/10/31 17:11:08 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	*dst;

	if (n == 0)
		return (0);
	i = 0;
	src = (unsigned char *) s1;
	dst = (unsigned char *) s2;
	if (!(src || dst))
		return (0);
	while (i < (n - 1) && src[i] && dst[i] && src[i] == dst[i])
		i++;
	return (src[i] - dst[i]);
}
/*
int main()
{
	char s1[] = "a";
	char s2[] = "b";

	printf("%d\n", ft_strncmp(s1, s2, 1));
}*/
