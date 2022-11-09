/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:49:24 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/09 21:00:44 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_parsing(t_data *data, t_parsing *parse, char **argv)
{
	ft_check_argument(argv);
	ft_check_file(parse, argv);
	ft_read_map(data, parse);
	ft_check_id(data, parse);
}

int	is_player(char c)
{
	if (c == 'N'|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_check_first_last(int i, char **map, t_data *data)
{
	if (i == 0 || i == ft_strlen2d(map) - 1)
		ft_check_first_line(map[i], data);
}

int	ft_check_middle(int i, int j, char **map, t_data *data)
{
	if (ft_is_whitespace(map[i][j]) == 1)
	{
		ft_check_around(map, i, j, data);
		return (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = y;
	while (i < y + 63)
	{
		j = x;
		while (j <= x + 63)
		{
			if (j == x + 63)
				my_mlx_pixel_put(data, j++, i, 0x000000);
			else
				my_mlx_pixel_put(data, j++, i, color);
		}
		i++;
	}
}

void	init_img(t_data *data)
{
	int	null;

	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

/*void	draw_3D(t_data *data)
{
	double	offset;
	int		x;
	double	center;

	center = WINDOW_WIDTH / 2;
	data->line_height = (64 * WINDOW_HEIGHT) / data->distance;
	printf("Line height : %f\n", data->line_height);
	offset = WINDOW_HEIGHT - data->line_height / 2;
	if (data->line_height > WINDOW_HEIGHT)
		data->line_height = WINDOW_HEIGHT;
	draw_column(data, x);
	//while(x <= WINDOW_WIDTH)
	//	draw_column(data, x++);
}*/

void	remove_distorsion(t_data *data)
{
	if (data->tmp_angle >= data->player_angle)
		data->distance = data->distance * cos(degree_to_radian(data->tmp_angle - data->player_angle));
	else
		data->distance = data->distance * cos(degree_to_radian(data->player_angle - data->tmp_angle));
}

void	fov_3d(t_data *data)
{
	int		x;

	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	x = 0;
	data->tmp_angle = data->player_angle + (FOV / 2);
	while (x < WINDOW_WIDTH)
	{
		if (data->tmp_angle > 360)
			data->tmp_angle = data->tmp_angle - 360;
		if (data->tmp_angle < 0)
			data->tmp_angle = 360 + data->tmp_angle;
		find_vertical_intersection(data);
		find_horizontal_intersection(data);
		find_distance(data);
		remove_distorsion(data);
		draw_3D(data, x);
		data->tmp_angle = data->tmp_angle - 0.046875;
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	draw_3D(t_data *data, int x)
{
	double	slice_height;
	int		y;
	int		w;
	double	center;
	double	dist_plane;
	double 	dist_before_wall;

	center = WINDOW_HEIGHT / 2;
	dist_plane = fabs((WINDOW_WIDTH / 2) / tan(degree_to_radian(FOV / 2)));
	slice_height = ceil((64 / data->distance) * dist_plane);
	if (slice_height > WINDOW_HEIGHT)
		slice_height = WINDOW_HEIGHT - 1;
	dist_before_wall = center - (slice_height / 2);
	y = 0;
	w = 0;
	//printf("Center = %f | Slice_height = %f | Distance = %f | Dist_plane = %f | Dist_before_wall = %f\n", center, slice_height, data->distance, dist_plane, dist_before_wall);
	while (y < dist_before_wall)
	{
		my_mlx_pixel_put(data, x, y, 0x000000);
		y++;
	}
	while (w < slice_height && w + y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(data, x, w + y, 0xFF0000);
		w++;
	}
	while (w + y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(data, x, w + y, 0xFFF000);
		w++;
	}
}

void	draw_player(t_data *data, int py, int px, int color)
{
	int i;
	int j;

	i = py;

	while (i <= py)
	{
		j = px;
		while (j <= px)
			if (data->win_ptr != NULL)
				my_mlx_pixel_put(data, j++, i, color);
		i++;
	}
}

void	draw_map(char **map, t_data *data)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0')
			{
				if (is_player(map[i][j]) == 1)
				{
					if (data->win_ptr != NULL)
					{
						draw_rect(data, j * 64, i * 64, 0xFFFFFF);
						draw_player(data, data->player_y, data->player_x, 0xFF0000);
					}
				}
				else if (map[i][j] == '1')
				{
					draw_rect(data, j * 64, i * 64, 0x0000FF);
					draw_player(data, data->player_y, data->player_x, 0xFF0000);
				}
			}
			else
				draw_rect(data, j * 64, i * 64, 0xFFFFFF);
		}
	}
}


void	window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	if (!data->win_ptr)
		ft_msg_free(data->map, "Error\nPB WINDOWS\n");
}


double	degree_to_radian(double r)
{
	return((r * (M_PI / 180)) + 0.001);
}

void	init_coordinates_horizontal(t_data *data, double *ya, double *ay)
{
	if (data->tmp_angle >= 0.0 && data->tmp_angle < 180.0)
	{
		*ya = -64.0;
		*ay = floor(data->player_y / 64.0) * (64.0) - 0.00000001;
	}
	else
	{
		*ya = 64.0;
		*ay = floor(data->player_y / 64.0) * (64.0) + 64;
	}
}

void	init_coordinates_vertical(t_data *data, double *xa, double *ax)
{
	if ((data->tmp_angle >= 0.0 && data->tmp_angle <= 90.0) || (data->tmp_angle >= 270.0 && data->tmp_angle <= 360.0))
	{
		*xa = 64.0;
		*ax = floor(data->player_x / 64.0) * (64.0) + 64.0;
	}
	else
	{
		*xa = -64.0;
		*ax = floor(data->player_x / 64.0) * (64.0) - 0.00000001;
	}
}

int	ft_biglen(char **s)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (s[i])
	{
		j = 0;
		while(s[i][j])
			j++;
		if (j > len)
			len = j;
		i++;
	}
	return (len);
}

int	check_hz_broke(t_data *data)
{
	if (!(floor(data->hz.tx / 64.0) >= 0 && floor(data->hz.tx / 64.0) < ft_biglen(data->s_map) - 1))
		return (1);

	return (0);
}

int	check_vt_broke(t_data *data)
{
	if (!(floor(data->vt.ty / 64.0) >= 0 && floor(data->vt.ty / 64.0) < ft_strlen2d(data->s_map) - 1))
		return (1);
	return (0);
}

void	find_horizontal_intersection(t_data *data)
{
	init_coordinates_horizontal(data, &data->hz.ya, &data->hz.ay);
	data->hz.xa = -(data->hz.ya) / tan(degree_to_radian(data->tmp_angle));
	data->hz.ty = data->hz.ay;
	data->hz.tx = data->player_x + (data->player_y - data->hz.ay) /
						tan(degree_to_radian(data->tmp_angle));
	if (check_hz_broke(data))
		return ;
	while (data->s_map[(int)floor(data->hz.ty / 64.0)][(int)floor(data->hz.tx / 64.0)] != '1')
	{
		data->hz.ax = data->player_x + (data->player_y - data->hz.ay) /
						tan(degree_to_radian(data->tmp_angle));
		data->hz.ty = data->hz.ay + data->hz.ya;
		data->hz.tx = data->hz.ax + data->hz.xa;
		data->hz.ay = data->hz.ty;
		data->hz.ax = data->hz.tx;
		if (check_hz_broke(data))
			return ;
	}
}

void	find_vertical_intersection(t_data *data)
{
	init_coordinates_vertical(data, &data->vt.xa, &data->vt.ax);
	data->vt.ya = -(data->vt.xa) * tan(degree_to_radian(data->tmp_angle));
	data->vt.ty = data->player_y + (data->player_x - data->vt.ax)
							* tan(degree_to_radian(data->tmp_angle));
	data->vt.tx = data->vt.ax ;
	if (check_vt_broke(data) == 1)
		return ;
	while (data->s_map[(int)floor(data->vt.ty / 64.0)][(int)floor(data->vt.tx / 64.0)] != '1')
	{
		data->vt.ay = data->player_y + (data->player_x - data->vt.ax)
							* tan(degree_to_radian(data->tmp_angle));
		data->vt.ty = data->vt.ay + data->vt.ya;
		data->vt.tx = data->vt.ax + data->vt.xa;
		data->vt.ay = data->vt.ty;
		data->vt.ax = data->vt.tx;
		if (check_vt_broke(data) == 1)
			return ;
	}
}

void	draw_rayon(t_data *data, double wall_x, double wall_y)
{
	int		steps;
	int		i;
	double	x;
	double	y;

	if (fabs(wall_x - data->player_x) >= fabs(wall_y - data->player_y))
		steps = fabs(wall_x - data->player_x);
	else
		steps = fabs(wall_y - data->player_y);
	i = 1;
	x = data->player_x;
	y = data->player_y;
	while (i <= steps)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0xFF0000);
		x += (wall_x - data->player_x) / steps;
		y += (wall_y - data->player_y) / steps;
		i++;
	}
}

void	find_distance(t_data *data)
{
	double dist_hz;
	double dist_vt;

	//printf("hz tx : %f hz ty : %f\n",data->hz.tx, data->hz.ty);
	//printf("player x : %fplayer y : %f\n",data->player_x, data->player_y);
	dist_hz = sqrt(pow(data->player_x - data->hz.tx, 2) + pow(data->player_y - data->hz.ty, 2));
	dist_vt = sqrt(pow(data->player_x - data->vt.tx, 2) + pow(data->player_y - data->vt.ty, 2));
	if (dist_hz == 0.0 && dist_vt == 0.0)
	{
		printf("--here--\n");
	}
	if (dist_hz == 0.0)
	{
		//draw_rayon(data, data->vt.tx, data->vt.ty);
		data->distance = dist_vt;
		return ;
	}
	if (dist_vt == 0.0)
	{
		//draw_rayon(data, data->hz.tx, data->hz.ty);
		data->distance = dist_hz;
		return ;
	}
	if (dist_hz < dist_vt)
	{
		data->distance = dist_hz;
		//draw_rayon(data, data->hz.tx, data->hz.ty);
	}
	else
	{
		data->distance = dist_vt;
		//draw_rayon(data, data->vt.tx, data->vt.ty);
	}
}

void	left_right(int keycode, t_data *data)
{
	if (keycode == LEFT_L)
	{
		if (data->player_angle + 3 > 360)
		{
			data->player_angle = 0;
			data->player_angle += 3;
		}
		else
			data->player_angle += 3;
	}
	if (keycode == RIGHT_L)
	{
		if (data->player_angle - 3 < 0)
		{
			data->player_angle = 360;
			data->player_angle -= 3;
		}
		else
			data->player_angle -= 3;
	}
}

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
	if (keycode == LEFT_L || keycode == RIGHT_L) // LEFT ET RIGHT
		left_right(keycode, data);
	if (keycode == W || keycode == S)
		up_back(keycode, data);
	if (keycode == A || keycode == D)
		step_side(keycode, data);
	mlx_destroy_image(data->mlx_ptr, data->img);
	fov_3d(data);
	//find_and_draw(data);
	return (0);
}

void	find_and_draw(t_data *data)
{
	int	steps;

	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	draw_map(data->s_map, data);
	data->tmp_angle = data->player_angle - (FOV / 2);
	steps = 1;
	while (steps <= FOV / 3)
	{
		if (data->tmp_angle > 360)
			data->tmp_angle = 1;
		if (data->tmp_angle < 0)
			data->tmp_angle = 360 + data->player_angle - (FOV / 2);
		find_horizontal_intersection(data);
		find_vertical_intersection(data);
		find_distance(data);
		data->tmp_angle += 3;
		steps++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	event(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_hook, data); // CHANGEZ KEYPRESS KEYPRESSMASK par 2 et 0
	//mlx_hook(data->win_ptr, 17, 0, closewd, data);
	mlx_loop(data->mlx_ptr);
}

void	draw_column(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < data->line_height)
	{
		my_mlx_pixel_put(data, x, y, 0xFF00FF);
		y++;
	}
}

void	start_display(t_data *data)
{
	window(data);
	fov_3d(data);
	//find_and_draw(data);
	event(data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_parsing	parse;

	start_parsing(&data, &parse, argv);
	start_display(&data);
	return (0);
}
