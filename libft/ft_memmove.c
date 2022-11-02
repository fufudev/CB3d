/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 08:30:39 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/19 13:31:47 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dest > source)
	{
		while (len--)
			dest[len] = source[len];
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
/* int	main()
{
	char str [] = "memmove can be very useful......";
	ft_memmove(str+20, str+15, 11);

	printf("%s\n", str);
	return (0);
}*/
