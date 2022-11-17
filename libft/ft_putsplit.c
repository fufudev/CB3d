/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:27:06 by ffiliz            #+#    #+#             */
/*   Updated: 2022/01/25 19:27:49 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putsplit(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		i++;
	}
}
