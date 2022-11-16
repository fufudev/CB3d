#include "../cub3d.h"

void	up(t_data *data, double *x_tmp, double *y_tmp)
{
	if ((size_t)floor((data->player_x + *x_tmp) / 64) < data->len
		&& (int)floor((data->player_y - *y_tmp) / 64) < data->big_len)
	{
		if (data->s_map[(int)floor(((data->player_y - *y_tmp) / 64))][(int)(floor((data->player_x + *x_tmp) / 64))] != '1')
		{
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
		if (data->s_map[(int)floor(((data->player_y + *y_tmp) / 64))][(int)(floor((data->player_x - *x_tmp) / 64))] != '1')
		{
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
		if (data->s_map[(int)floor(((data->player_y + *y_tmp) / 64))][(int)(floor((data->player_x - *x_tmp) / 64))] != '1')
		{
			data->player_x -= *x_tmp;
			data->player_y += *y_tmp;
		}
	}
}

void	right_side(t_data *data, double *x_tmp, double *y_tmp)
{
	if ((size_t)floor((data->player_x + *x_tmp) / 64) < data->len
		&& (int)floor((data->player_y - *y_tmp) / 64) < data->big_len)
	{
		if (data->s_map[(int)floor(((data->player_y - *y_tmp) / 64))][(int)(floor((data->player_x + *x_tmp) / 64))] != '1')
		{
			data->player_x += *x_tmp;
			data->player_y -= *y_tmp;
		}
	}
}