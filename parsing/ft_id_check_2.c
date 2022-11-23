/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_id_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:33:39 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/23 09:06:06 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_replace_space_by_one(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->s_map[i])
	{
		while (data->s_map[i][j])
		{
			if (data->s_map[i][j] == ' ')
				data->s_map[i][j] = '1';
			j++;
		}
		j = 0;
		i++;
	}
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

int	ft_strlen_int(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
