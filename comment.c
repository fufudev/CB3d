/*void	draw_texture(t_data *data, int x, int y, void *text)
{
	data->addr[(y * data->line_length + x * (data->bits_per_pixel / 8))] = text.addr[(y * text.line_length + x * (text.bits_per_pixel / 8)) % data->offset];
}*/

/*void	draw_rect(t_data *data, int x, int y, int color)
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
}*/

/*void	draw_rayon(t_data *data, double wall_x, double wall_y)
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
}*/