/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:50:32 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/23 10:43:19 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_positionn(t_data *data, int i, int j)
{
	data->pos_y = i;
	data->pos_x = j;
	data->player_y = i * 64 + 32;
	data->player_x = j * 64 + 32;
	check_overflow_map(data, i, j);
	data->indic = 1;
}

void	check_overflow_map(t_data *data, int i, int j)
{
	if (i > 0 && i < (int)ft_strlen2d(data->s_map))
	{
		if (j >= ft_strlen_int(data->s_map[i - 1]))
			ft_msg_free(data->map, "Error\nOut of map\n");
		if (j >= ft_strlen_int(data->s_map[i + 1]))
			ft_msg_free(data->map, "Error\nOut of map\n");
	}
}

void	ft_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
