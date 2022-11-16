#include "../cub3d.h"

void	find_horizontal_intersection(t_data *d)
{
	init_coordinates_horizontal(d, &d->hz.ya, &d->hz.ay);
	d->hz.xa = -(d->hz.ya) / tan(degree_to_radian(d->tmp_angle));
	d->hz.ty = d->hz.ay;
	d->hz.tx = d->player_x + (d->player_y - d->hz.ay) /
						tan(degree_to_radian(d->tmp_angle));
	if (check_hz_broke(d))
		return ;
	while (d->s_map[(int)floor(d->hz.ty / 64.0)][(int)floor(d->hz.tx / 64.0)] != '1'
			&& d->s_map[(int)floor(d->hz.ty / 64.0)][(int)floor(d->hz.tx / 64.0)] != ' '
				&& d->s_map[(int)floor(d->hz.ty / 64.0)][(int)floor(d->hz.tx / 64.0)] != '\0')
	{
		d->hz.ax = d->player_x + (d->player_y - d->hz.ay) /
						tan(degree_to_radian(d->tmp_angle));
		d->hz.ty = d->hz.ay + d->hz.ya;
		d->hz.tx = d->hz.ax + d->hz.xa;
		d->hz.ay = d->hz.ty;
		d->hz.ax = d->hz.tx;
		if (check_hz_broke(d))
			return ;
	}
}

void	find_vertical_intersection(t_data *d)
{
	init_coordinates_vertical(d, &d->vt.xa, &d->vt.ax);
	d->vt.ya = -(d->vt.xa) * tan(degree_to_radian(d->tmp_angle));
	d->vt.ty = d->player_y + (d->player_x - d->vt.ax)
							* tan(degree_to_radian(d->tmp_angle));
	d->vt.tx = d->vt.ax ;
	if (check_vt_broke(d) == 1)
		return ;
	while (d->s_map[(int)floor(d->vt.ty / 64.0)][(int)floor(d->vt.tx / 64.0)] != '1'
			&& d->s_map[(int)floor(d->vt.ty / 64.0)][(int)floor(d->vt.tx / 64.0)] != ' '
				&& d->s_map[(int)floor(d->vt.ty / 64.0)][(int)floor(d->vt.tx / 64.0)] != '\0')
	{
		d->vt.ay = d->player_y + (d->player_x - d->vt.ax)
							* tan(degree_to_radian(d->tmp_angle));
		d->vt.ty = d->vt.ay + d->vt.ya;
		d->vt.tx = d->vt.ax + d->vt.xa;
		d->vt.ay = d->vt.ty;
		d->vt.ax = d->vt.tx;
		if (check_vt_broke(d) == 1)
			return ;
	}
}

void	get_sqrt(t_data *data, double *dist_hz, double *dist_vt)
{
	*dist_hz = sqrt(pow(data->player_x - data->hz.tx, 2)
				+ pow(data->player_y - data->hz.ty, 2));
	*dist_vt = sqrt(pow(data->player_x - data->vt.tx, 2)
				+ pow(data->player_y - data->vt.ty, 2));
}

void	find_distance(t_data *data)
{
	double	dist_hz;
	double	dist_vt;

	get_sqrt(data, &dist_hz, &dist_vt);
	if (dist_hz == 0.0)
	{
		data->distance = dist_vt;
		save_distance(data, data->vt.tx, data->vt.ty, 1);
		return ;
	}
	if (dist_vt == 0.0)
	{
		data->distance = dist_hz;
		save_distance(data, data->hz.tx, data->hz.ty, 0);
		return ;
	}
	if (dist_hz < dist_vt)
	{
		data->distance = dist_hz;
		save_distance(data, data->hz.tx, data->hz.ty, 0);
	}
	else
	{
		data->distance = dist_vt;
		save_distance(data, data->vt.tx, data->vt.ty, 1);
	}
}

