/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:50:32 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/17 21:54:37 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_positionn(t_data *data, int i, int j)
{
	data->pos_y = i;
	data->pos_x = j;
	data->player_y = i * 64 + 32;
	data->player_x = j * 64 + 32;
	data->indic = 1;
}

void	ft_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
