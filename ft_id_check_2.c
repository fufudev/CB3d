/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_id_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:33:39 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:33:41 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_c_or_f(char *str, t_data *data)
{
	int	i;

	i = 0;
	if ((str[i] == 'F' || str[i] == 'C') && str[i + 1] == ' ')
		return (1);
	else
		ft_msg_free(data->map, "Error\nMap incorrect.\n");
	return (0);
}

void	ft_check_value(int tmp_atoi, t_data *data)
{
	if (tmp_atoi >= 0 && tmp_atoi <= 255)
		return ;
	else
		ft_msg_free(data->map, "Error\nValue too big\n");
}

void	ft_swoosh(int *swoosh, char c, int *i)
{
	if ((*swoosh == 1) && c == ',')
	{
		if (c == ',')
		{
			(*i)++;
			*swoosh = 0;
		}
	}
}
