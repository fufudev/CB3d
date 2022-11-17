/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:58:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/17 18:56:22 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_left_distance(t_data *data, double x_tmp, double y_tmp)
{
	data->player_x -= x_tmp;
	data->player_y += y_tmp;
	data->tmp_angle += 60;
	if (data->tmp_angle > 360)
		data->tmp_angle = data->tmp_angle - 360;
	if (data->tmp_angle < 0)
		data->tmp_angle = 360 + data->tmp_angle;
	find_vertical_intersection(data);
	find_horizontal_intersection(data);
	find_distance(data);
	data->player_x += x_tmp;
	data->player_y -= y_tmp;
	data->tmp_angle -= 60;
	if (data->distance < 30)
		return (1);
	else
		return (0);
}

int	check_right_distance(t_data *data, double x_tmp, double y_tmp)
{
	data->player_x += x_tmp;
	data->player_y -= y_tmp;
	data->tmp_angle -= 60;
	if (data->tmp_angle > 360)
		data->tmp_angle = data->tmp_angle - 360;
	if (data->tmp_angle < 0)
		data->tmp_angle = 360 + data->tmp_angle;
	find_vertical_intersection(data);
	find_horizontal_intersection(data);
	find_distance(data);
	data->player_x -= x_tmp;
	data->player_y += y_tmp;
	data->tmp_angle += 60;
	if (data->distance < 30)
		return (1);
	else
		return (0);
}

int	check_up_distance(t_data *data, double x_tmp, double y_tmp)
{
	data->player_x += x_tmp;
	data->player_y -= y_tmp;
	find_vertical_intersection(data);
	find_horizontal_intersection(data);
	find_distance(data);
	data->player_x -= x_tmp;
	data->player_y += y_tmp;
	if (data->distance < 30)
		return (1);
	else
		return (0);
}

int	check_back_distance(t_data *data, double x_tmp, double y_tmp)
{
	data->player_x -= x_tmp;
	data->player_y += y_tmp;
	data->tmp_angle += 180;
	if (data->tmp_angle > 360)
		data->tmp_angle = data->tmp_angle - 360;
	if (data->tmp_angle < 0)
		data->tmp_angle = 360 + data->tmp_angle;
	find_vertical_intersection(data);
	find_horizontal_intersection(data);
	find_distance(data);
	data->player_x += x_tmp;
	data->player_y -= y_tmp;
	data->tmp_angle -= 180;
	if (data->distance < 30)
		return (1);
	else
		return (0);
}
