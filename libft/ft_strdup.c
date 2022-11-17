/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:16:43 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/19 13:31:35 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*pt;

	i = 0;
	pt = malloc(sizeof (char) * ft_strlen(s1) + 1);
	if (!pt)
		return (NULL);
	while (s1[i])
	{
		pt[i] = s1[i];
		i++;
	}
	pt[i] = '\0';
	return (pt);
}
/*void	main(int ac, char **av)
{
	printf("%s\n", ft_strdup(av[1]));
}*/
