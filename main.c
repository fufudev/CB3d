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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

/*void	init_value_pos(t_data *data)
{

}*/

void	start_display(t_data *data)
{
	//init_value_pos(data);
	window(data);
	find_horizontal_intersection(data);
	find_vertical_intersection(data);
	mlx_loop(data->mlx_ptr);
	//event(data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_parsing	parse;

	start_parsing(&data, &parse, argv);
	start_display(&data);
	return (0);
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
		*ax = floor(data->player_y / 64) * (64) - 1;
	}
	else
	{
		*xa = 64;
		*ax = floor(data->player_y / 64) * (64) + 64;
	}
}

void	find_horizontal_intersection(t_data *data)
{
	double	xa;
	double	ya;
	double	ay;
	double	ax;
	double	tx;
	double	ty;

	ty = floor(data->player_y);
	tx = floor(data->player_x);
	data->player_angle = 60.0;
	xa = floor(64 / tan(degree_to_radian(60)));
	init_coordinates_horizontal(data, &ya, &ay);
	while (data->s_map[(int)floor(ty / 64)][(int)floor(tx / 64)] != '1')
	{
		ax = floor(data->player_x + (data->player_y - ay) / tan(degree_to_radian(60)));
		ty = ay + ya;
		tx = ax + xa;
		ay = ty;
		ax = tx;
	}
}

void	find_vertical_intersection(t_data *data)
{
	double	xa;
	double	ya;
	double	ay;
	double	ax;
	double	tx;
	double	ty;

	ty = floor(data->player_y);
	tx = floor(data->player_x);
	data->player_angle = 60.0;
	ya = floor(64 / tan(degree_to_radian(60)));
	init_coordinates_vertical(data, &ya, &ay);
	while (data->s_map[(int)floor(ty / 64)][(int)floor(tx / 64)] != '1')
	{
		ay = floor(data->player_y + (data->player_x - ax) / tan(degree_to_radian(60)));
		ty = ay + ya;
		tx = ax + xa;
		ay = ty;
		ax = tx;
	}
	printf("ty : %f tx : %f\n", floor(ty / 64), floor(tx / 64));
}
/*void	event(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, key_hook, data);
	mlx_hook(data->win_ptr, 17, 0, closewd, data);
	mlx_loop_hook(data->mlx_ptr, draw_again, data);
	mlx_loop(data->mlx_ptr);
}
*/


