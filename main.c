/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:49:24 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/02 17:20:01 by anggonza         ###   ########.fr       */
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
	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	draw_map(data->s_map, data);
}	


double	degree_to_radian(double r)
{	
	return(r * 3.14 / 180);
}

void	init_coordinates_horizontal(t_data *data, double *ya, double *ay)
{
	if (data->player_angle > 0 && data->player_angle < 180)
	{
		*ya = -64;
		*ay = floor(data->player_y / 64) * (64) - 1;
	}
	else
	{
		*ya = 64;
		*ay = floor(data->player_y / 64) * (64) + 64;
	}
}

void	init_coordinates_vertical(t_data *data, double *xa, double *ax)
{
	if (data->player_angle > 90 && data->player_angle < 270)
	{
		*xa = -64;
		*ax = floor(data->player_x / 64) * (64) - 1;
	}
	else
	{
		*xa = 64;
		*ax = floor(data->player_x / 64) * (64) + 64;
	}
}

void	find_horizontal_intersection(t_data *data)
{
	data->hz.ty = floor(data->player_y);
	data->hz.tx = floor(data->player_x);
	data->hz.xa = floor(64 / tan(degree_to_radian(data->player_angle)));
	init_coordinates_horizontal(data, &data->hz.ya, &data->hz.ay);
	while (data->s_map[(int)floor(data->hz.ty / 64)][(int)floor(data->hz.tx / 64)] != '1')
	{
		data->hz.ax = floor(data->player_x + (data->player_y - data->hz.ay) / 
						tan(degree_to_radian(data->player_angle)));
		data->hz.ty = data->hz.ay + data->hz.ya;
		data->hz.tx = data->hz.ax + data->hz.xa;
		data->hz.ay = data->hz.ty;
		data->hz.ax = data->hz.tx;
		if (data->hz.tx < 0 || data->hz.tx > ft_strlen(data->s_map[floor(data->hz.ty / 64)]) - 1) //ICI check xa
		{
			data->hz.ty = data->player_y;
			data->hz.tx = data->player_x;
			break ;
		}
	}
	printf("Horizontal check :\n(%0.f, %0.f)\n", floor(data->hz.tx / 64), floor(data->hz.ty / 64));
}

void	find_vertical_intersection(t_data *data)
{
	data->vt.ty = floor(data->player_y);
	data->vt.tx = floor(data->player_x);
	data->vt.ya = floor(64 * tan(degree_to_radian(data->player_angle)));
	init_coordinates_vertical(data, &data->vt.xa, &data->vt.ax);
	while (data->s_map[(int)floor(data->vt.ty / 64)][(int)floor(data->vt.tx / 64)] != '1' && data->vt.ya != -1)
	{
		data->vt.ay = floor(data->player_y + (data->player_x - data->vt.ax) *
						 tan(degree_to_radian(data->player_angle)));
		data->vt.ty = data->vt.ay - data->vt.ya;
		data->vt.tx = data->vt.ax + data->vt.xa;
		data->vt.ay = data->vt.ty;
		data->vt.ax = data->vt.tx;
		if (data->vt.ty < 0 || data->vt.ty > ft_strlen(data->s_map[]) - 1) //ICI check ya
		{
			data->vt.ty = data->player_y;
			data->vt.tx = data->player_x;
			break ;
		}
		printf("Ty : %f Tx : %f\n", data->vt.ty, data->vt.tx);
	}
	printf("Vertical check :\n(%0.f, %0.f)\n", floor(data->vt.tx / 64), floor(data->vt.ty / 64));
}

void	draw_rayon(t_data *data, double wall_x, double wall_y)
{
	double	m;
	int		steps;
	int		i;
	double	x;
	double	y;

	m = wall_y - data->player_y / wall_x - data->player_x;
	if (wall_x - data->player_x > wall_y - data->player_y)
		steps = fabs(wall_x - data->player_x);
	else
		steps = fabs(wall_y - data->player_y);
	i = 1;
	x = data->player_x;
	y = data->player_y;
	while (i <= steps)
	{
		my_mlx_pixel_put(data, floor(x), floor(y), 0xFF0000);
		x += (wall_x - data->player_x) / steps;
		y += (wall_y - data->player_y) / steps;
		i++;
	}
}

void	find_distance(t_data *data)
{
	double pd;
	double pe;
		
	pd = sqrt(pow(data->player_x - data->hz.tx, 2) + pow(data->player_y - data->hz.ty, 2));
	pe = sqrt(pow(data->player_x - data->vt.tx, 2) + pow(data->player_y - data->vt.ty, 2));
	if (floor(pd) < floor(pe))
		draw_rayon(data, data->hz.tx, data->hz.ty);
	else
		draw_rayon(data, data->vt.tx, data->vt.ty);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == LEFT)
	{
		if (data->player_angle + 1 > 360)
		{
			data->player_angle = 0;
			data->player_angle += 1;
		}
		else
			data->player_angle += 1;
	}
	if (keycode == RIGHT)
	{
		printf("A droite \n");
		if (data->player_angle - 1 < 0)
		{
			data->player_angle = 360;
			data->player_angle -= 1;
		}
		else
			data->player_angle -= 1;
	}
	find_and_draw(data);
	return (0);
}

void	find_and_draw(t_data *data)
{
	find_horizontal_intersection(data);
	find_vertical_intersection(data);
	find_distance(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	event(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, key_hook, data);
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


//Attention a ya et xa qui parte en couille lorsqu'il n'ya pas d'intersection.
