/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:49:24 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/05 20:05:57 by anggonza         ###   ########.fr       */
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
	if (data->player_angle >= 0.0 && data->player_angle < 180.0)
	{
		*ya = -64.0;
		*ay = floor(data->player_y / 64.0) * (64.0) - 1.0;
	}
	else
	{
		*ya = 64.0;
		*ay = floor(data->player_y / 64.0) * (64.0) + 64;
	}
}

void	init_coordinates_vertical(t_data *data, double *xa, double *ax)
{
	if ((data->player_angle >= 0.0 && data->player_angle <= 90.0) || (data->player_angle >= 270.0 && data->player_angle <= 360.0))
	{
		*xa = 64.0;
		*ax = floor(data->player_x / 64.0) * (64.0) + 64.0;
	}
	else
	{
		*xa = -64.0;
		*ax = floor(data->player_x / 64.0) * (64.0) - 1.0;
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
	if (!(floor(data->hz.tx / 64.0) > 0 && floor(data->hz.tx / 64.0) < ft_biglen(data->s_map) - 1))
	{
		data->hz.ty = data->player_y;
		data->hz.tx = data->player_x;
		return (1);
	}
	return (0);
}


int	check_vt_broke(t_data *data)
{
	if (!(floor(data->vt.ty / 64.0) >= 0 && floor(data->vt.ty / 64.0) < ft_strlen2d(data->s_map) - 1))
	{
		data->vt.ty = data->player_y;
		data->vt.tx = data->player_x;
		return (1);
	}
	return (0);
}

void	find_horizontal_intersection(t_data *data)
{
	init_coordinates_horizontal(data, &data->hz.ya, &data->hz.ay);
	data->hz.xa = -(data->hz.ya) / tan(degree_to_radian(data->player_angle));
	data->hz.ty = data->hz.ay;
	data->hz.tx = data->player_x + (data->player_y - data->hz.ay) / 
						tan(degree_to_radian(data->player_angle));
	if (check_hz_broke(data))
		return ;
	//printf("\nHorizontal - Ty : %f Tx : %f\n", data->hz.ty, data->hz.tx);
	while (data->s_map[(int)floor(data->hz.ty / 64.0)][(int)floor(data->hz.tx / 64.0)] != '1')
	{
		data->hz.ax = data->player_x + (data->player_y - data->hz.ay) / 
						tan(degree_to_radian(data->player_angle));
		data->hz.ty = data->hz.ay + data->hz.ya;
		data->hz.tx = data->hz.ax + data->hz.xa;
		data->hz.ay = data->hz.ty;
		data->hz.ax = data->hz.tx;
		if (check_hz_broke(data))
			return ;
		//printf("\nHorizontal - Ty : %f Tx : %f\n", data->hz.ty, data->hz.tx);	
	}
	//printf("\nHorizontal check :\n(%0.f, %0.f)\n", floor(data->hz.tx / 64.0), floor(data->hz.ty / 64.0));
}

void	find_vertical_intersection(t_data *data)
{
	init_coordinates_vertical(data, &data->vt.xa, &data->vt.ax);
	data->vt.ya = -(data->vt.xa) * tan(degree_to_radian(data->player_angle));
	data->vt.ty = data->player_y + (data->player_x - data->vt.ax)
							* tan(degree_to_radian(data->player_angle));
	data->vt.tx = data->vt.ax ;
	if (check_vt_broke(data) == 1)
		return ;
	//printf("Ici ty : %f | tx : %f\n", floor(data->vt.ty / 64.0), floor(data->vt.tx / 64.0));
	while (data->s_map[(int)floor(data->vt.ty / 64.0)][(int)floor(data->vt.tx / 64.0)] != '1')
	{
		data->vt.ay = data->player_y + (data->player_x - data->vt.ax)
							* tan(degree_to_radian(data->player_angle));
		data->vt.ty = data->vt.ay + data->vt.ya;
		data->vt.tx = data->vt.ax + data->vt.xa;
		data->vt.ay = data->vt.ty;
		data->vt.ax = data->vt.tx;
		if (check_vt_broke(data) == 1)
			return ;
		//printf("\nVertical - Ty : %f Tx : %f\n", data->vt.ty, data->vt.tx);
	}
	//printf("\nVertical check :\n(%0.f, %0.f)\n", floor(data->vt.tx / 64.0), floor(data->vt.ty / 64.0));
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
	//printf("Player X : %f | Player Y : %f\n", x, y);
	//printf("Wall_x = %d Wall_y = %f\n", (int)wall_x, wall_y);
	//printf("Steps : %d | x : %f | y : %f | dx : %f | dy : %f\n", steps, x, y, floor(wall_x) - data->player_x, floor(wall_y) - data->player_y);
	while (i <= steps)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0xFF0000);
		x += (wall_x - data->player_x) / steps;
		y += (wall_y - data->player_y) / steps;
		//printf("Player X : %f | Player Y : %f\n", x, y);
		i++;
	}
}

void	find_distance(t_data *data)
{
	double dist_hz;
	double dist_vt;
		
	dist_hz = sqrt(pow(data->player_x - data->hz.tx, 2) + pow(data->player_y - data->hz.ty, 2));
	dist_vt = sqrt(pow(data->player_x - data->vt.tx, 2) + pow(data->player_y - data->vt.ty, 2));
	//printf("Distance hz : %f Distance verticale : %f\n", dist_hz, dist_vt);
	if (dist_hz == 0.0)
	{
		draw_rayon(data, data->vt.tx, data->vt.ty);
		return ;
	}
	if (dist_vt == 0.0)
	{
		draw_rayon(data, data->hz.tx, data->hz.ty);
		return ;
	}
	if (dist_hz < dist_vt)
		draw_rayon(data, data->hz.tx, data->hz.ty);
	else
		draw_rayon(data, data->vt.tx, data->vt.ty);
}

void	left_right(int keycode, t_data *data)
{
	if (keycode == LEFT_L)
	{
		if (data->player_angle + 1 > 360)
		{
			data->player_angle = 0;
			data->player_angle += 1;
		}
		else
			data->player_angle += 1;
	}
	if (keycode == RIGHT_L)
	{
		if (data->player_angle - 1 < 0)
		{
			data->player_angle = 360;
			data->player_angle -= 1;
		}
		else
			data->player_angle -= 1;
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
		printf("here4\n");
		if (data->s_map[(int)floor(((data->player_y + *y_tmp) / 64))][(int)(floor((data->player_x - *x_tmp) / 64))] != '1')
		{
			printf("here5\n");
			// if (data->player_x) faire + x et - y si en haut et l'inverse si en bas je pense !
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
		printf("here2\n");
		if (data->s_map[(int)floor(((data->player_y - *y_tmp) / 64))][(int)(floor((data->player_x + *x_tmp) / 64))] != '1')
		{
			printf("here3\n");
			data->player_x += *x_tmp;
			data->player_y -= *y_tmp;
		}
	}
}

void	step_side(int keycode, t_data *data)
{
	double	x_tmp;
	double	y_tmp;

	if  (data->player_angle >= 90 && data->player_angle <= 270)
	{
		x_tmp = cos(degree_to_radian(data->player_angle - 90.0)) * data->speed;
		y_tmp = sin(degree_to_radian(data->player_angle - 90.0)) * data->speed;
	}
	else
	{
		x_tmp = cos(degree_to_radian(data->player_angle + 90.0)) * data->speed;
		y_tmp = sin(degree_to_radian(data->player_angle + 90.0)) * data->speed;
	}
	data->big_len = ft_biglen(data->s_map) - 1;
	data->len = ft_strlen(data->s_map[(int)floor(data->player_y / 64)]) - 1;
	printf("here1\n");
	if (keycode == A)
		left_side(data, &x_tmp, &y_tmp);
	if (keycode == D)
		right_side(data, &x_tmp, &y_tmp);
}

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == LEFT_L || keycode == RIGHT_L) // LEFT RIGHT
		left_right(keycode, data);
	if (keycode == W || keycode == S)
		up_back(keycode, data);
	if (keycode == A || keycode == D)
		step_side(keycode, data);
	mlx_destroy_image(data->mlx_ptr, data->img);
	find_and_draw(data);
	return (0);
}

void	find_and_draw(t_data *data)
{
	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	draw_map(data->s_map, data);
	find_horizontal_intersection(data);
	find_vertical_intersection(data);
	find_distance(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	event(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_hook, data); // CHANGEZ KEYPRESS KEYPRESSMASK
	//mlx_hook(data->win_ptr, 17, 0, closewd, data);
	mlx_loop(data->mlx_ptr);
}

void	start_display(t_data *data)
{
	window(data);
	find_and_draw(data);
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
