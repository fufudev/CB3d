/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:20:38 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/17 19:20:39 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	left_right(int keycode, t_data *data)
{
	if (keycode == LEFT)
	{
		if (data->player_angle + 5 > 360)
		{
			data->player_angle = 0;
			data->player_angle += 5;
		}
		else
			data->player_angle += 5;
	}
	if (keycode == RIGHT)
	{
		if (data->player_angle - 5 < 0)
		{
			data->player_angle = 360;
			data->player_angle -= 5;
		}
		else
			data->player_angle -= 5;
	}
}

void	up_back(int keycode, t_data *data)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = cos(degree_to_radian(data->player_angle)) * data->speed;
	y_tmp = sin(degree_to_radian(data->player_angle)) * data->speed;
	data->big_len = ft_biglen(data->s_map) - 1;
	data->len = ft_strlen(data->s_map[(int)floor(data->player_y / 64)]) - 1;
	if (keycode == W)
		up(data, &x_tmp, &y_tmp);
	if (keycode == S)
		back(data, &x_tmp, &y_tmp);
}

void	step_side(int keycode, t_data *data)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = cos(degree_to_radian(data->player_angle - 90.0)) * data->speed;
	y_tmp = sin(degree_to_radian(data->player_angle - 90.0)) * data->speed;
	data->big_len = ft_biglen(data->s_map) - 1;
	data->len = ft_strlen(data->s_map[(int)floor(data->player_y / 64)]) - 1;
	if (keycode == A)
		left_side(data, &x_tmp, &y_tmp);
	if (keycode == D)
		right_side(data, &x_tmp, &y_tmp);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == LEFT || keycode == RIGHT)
		left_right(keycode, data);
	if (keycode == W || keycode == S)
		up_back(keycode, data);
	if (keycode == A || keycode == D)
		step_side(keycode, data);
	if (keycode == ESC)
		escape(data);
	mlx_destroy_image(data->mlx_ptr, data->img);
	fov_3d(data);
	return (0);
}
