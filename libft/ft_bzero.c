/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:45:19 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/10 16:06:39 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*#include <stdio.h>*/
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dst;

	i = 0;
	dst = (unsigned char *) s;
	while (i < n)
	{
		dst[i] = 0;
		i++;
	}
}
/*
int	main()
{
	char test [] = {43, 41, 35, 76, 34, 43};
	bzero(test, 6);

	int i = 0;
	while(i < 6)
	{
		printf("%d\n", test[i]);
		i++;
	}
}*/
