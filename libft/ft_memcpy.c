/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:05:03 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/10 16:09:14 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst1;
	const char		*s;

	i = 0;
	dst1 = (unsigned char *) dst;
	s = (const char *) src;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		dst1[i] = s[i];
		i++;
	}
	return (dst1);
}
/*
int	main()
{
	char test [] = {43, 53, 68, 25, 10};
	char test2 [] = {65,85, 52, 89, 13};

	ft_memcpy(test, test2, 5);

	int i = 0;
	while (i < 5)
	{
		printf("%d\n", test[i]);
		i++;
	}
}
*/
