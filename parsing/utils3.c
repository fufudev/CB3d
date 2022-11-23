/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:50:32 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/23 09:54:03 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_positionn(t_data *data, int i, int j)
{
	data->pos_y = i;
	data->pos_x = j;
	data->player_y = i * 64 + 32;
	data->player_x = j * 64 + 32;
	if (data->pos_y > 0 && data->pos_y < (int)ft_strlen2d(data->s_map))
	{
		if (data->pos_x >= ft_strlen_int(data->s_map[data->pos_y - 1]))
			ft_msg_free(data->map, "Player out of map\n");
		if (data->pos_x >= ft_strlen_int(data->s_map[data->pos_y + 1]))
			ft_msg_free(data->map, "Player out of map\n");
	}
	data->indic = 1;
}

void	ft_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
