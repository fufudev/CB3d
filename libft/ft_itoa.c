/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:25:38 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/10 16:07:32 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	taille_nombre(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (i + 1);
	if (n > 0)
	{
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
	}
	else if (n < 0)
	{
		while (n < 0)
		{
			n = n / 10;
			i++;
		}
		return (i + 1);
	}
	return (i);
}

static char	*positive(char const *str, int n)
{
	int		len;
	char	*pt;

	len = taille_nombre(n);
	pt = (char *)str;
	while (len >= 1)
	{
		pt[len - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (pt);
}

static char	*negative(char const *str, int n)
{
	int		len;
	char	*pt;

	pt = (char *)str;
	len = taille_nombre(n);
	pt[0] = '-';
	if (n < 0)
		n = -n;
	while (len > 1)
	{
		pt[len - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (pt);
}

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = taille_nombre(n);
	str = (char *) malloc (sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(str, "-2147483648"));
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		negative(str, n);
	else
		positive(str, n);
	return (str);
}
