/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:28:14 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/20 00:00:37 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*dst;

	i = 0;
	dst = (unsigned char *) b;
	while (i < len)
	{
		dst[i] = (unsigned char) c;
		i++;
	}
	return (dst);
}
/*
int	main()
{
	char test [] = {0, 52, 55, 82, 51};
	ft_memset(test, 2, 5);

	int i = 0;
	while(i < 5)
	{
		printf("%d\n", test[i]);
		i++;
	}
}
*/
