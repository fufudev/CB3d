/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:17:51 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/19 22:56:45 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	i;
	char	*pt;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	pt = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
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
	return (pt);
}
/*int     main()
{
        char s1[] = "Aloura";
        char s2[] = "bebe";
        char *res = ft_strjoin(s1, s2);

        printf("%s\n", res);
        return 0;
}*/
