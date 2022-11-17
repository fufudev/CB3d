/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:11:58 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/17 19:12:11 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	up(t_data *data, double *x_tmp, double *y_tmp)
{
	if ((size_t)floor((data->player_x + *x_tmp) / 64) < data->len
		&& (int)floor((data->player_y - *y_tmp) / 64) < data->big_len)
	{
		if (data->s_map[(int)floor(((data->player_y - *y_tmp) / 64))]
			[(int)(floor((data->player_x + *x_tmp) / 64))] != '1')
		{
			if (check_up_distance(data, *x_tmp, *y_tmp))
				return ;
			data->player_x += *x_tmp;
			data->player_y -= *y_tmp;
		}
	}
}

void	back(t_data *data, double *x_tmp, double *y_tmp)
{
	if (((size_t)floor((data->player_x - *x_tmp) / 64) < data->len
			&& (int)floor((data->player_y + *y_tmp) / 64) < data->big_len))
	{
		if (data->s_map[(int)floor(((data->player_y + *y_tmp) / 64))]
			[(int)(floor((data->player_x - *x_tmp) / 64))] != '1')
		{
			if (check_back_distance(data, *x_tmp, *y_tmp))
				return ;
			data->player_x -= *x_tmp;
			data->player_y += *y_tmp;
		}
	}
}

void	left_side(t_data *data, double *x_tmp, double *y_tmp)
{
	if (((size_t)floor((data->player_x - *x_tmp) / 64) < data->len
			&& (int)floor((data->player_y + *y_tmp) / 64) < data->big_len))
	{
		if (data->s_map[(int)floor(((data->player_y + *y_tmp) / 64))]
			[(int)(floor((data->player_x - *x_tmp) / 64))] != '1')
		{
			if (check_left_distance(data, *x_tmp, *y_tmp))
				return ;
			data->player_x -= *x_tmp;
			data->player_y += *y_tmp;
		}
	}
}

void	right_side(t_data *data, double *x, double *y)
{
	if ((size_t)floor((data->player_x + *x) / 64) < data->len
		&& (int)floor((data->player_y - *y) / 64) < data->big_len)
	{
		if (data->s_map[(int)floor(((data->player_y - *y) / 64))]
			[(int)(floor((data->player_x + *x) / 64))] != '1')
		{
			if (check_right_distance(data, *x, *y))
				return ;
			data->player_x += *x;
			data->player_y -= *y;
		}
	}
}
