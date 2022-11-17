/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:53:42 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/10 16:17:09 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen (s);
	if (!s)
		return (NULL);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *) s + i);
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)s - i);
	else
		return (0);
}
/*int main()
{
	int l;
	char a[] = "aloura frero";
	printf("%s", ft_strrchr(a, l));
	return 0;
}*/
