#include "../cub3d.h"

int	rgb_to_int(int *tab)
{
	return (65536 * tab[0] + 256 * tab[1] + tab[2]);
}

void	draw_column(t_data *data, int x)
{
	long	y;

	y = 0;
	while (y < data->line_height)
	{
		my_mlx_pixel_put(data, x, y, 0xFF00FF);
		y++;
	}
}

void	get_color(t_data *data, int x, int y, int orientation)
{
	int	color;
	
	if ((data->tmp_angle >= 0 && data->tmp_angle <= 180) && orientation == 0)
	{
		color = data->a_no[data->txt_x + data->txt_y * 64];
		my_mlx_pixel_put(data, x, y, color);
	}
	else if ((data->tmp_angle >= 180 && data->tmp_angle <= 360) && orientation == 0)
	{
		color = data->a_so[data->txt_x + data->txt_y * 64];
		my_mlx_pixel_put(data, x, y, color);
	}
	else if ((data->tmp_angle >= 90 && data->tmp_angle <= 270) && orientation == 1)
	{
		color = data->a_we[data->txt_x + data->txt_y * 62];
		my_mlx_pixel_put(data, x, y, color);
	}
	else
	{
		color = data->a_ea[data->txt_x + data->txt_y * 64];
		my_mlx_pixel_put(data, x, y, color);
	}
}

void	draw_texture(t_data *data, int x, int p)
{
	if (data->orientation == 0)
		data->txt_x = fmod(data->pos_x / 64.0, 1.0) * 64.0;
	if (data->orientation == 1)
		data->txt_x = fmod(data->pos_y / 64.0, 1.0) * 64.0;
	data->txt_y = ((1.0 - (double)(data->dist_before_wall - p))
		/ data->slice_height) * 64.0;
	data->index = data->txt_x + (data->txt_y * 64.0);
	get_color(data, x, p, data->orientation);
}

void	draw_3D(t_data *data, int x)
{
	int		y;
	int		w;

	data->center = WINDOW_HEIGHT / 2;
	data->dist_plane = fabs((WINDOW_WIDTH / 2) / tan(degree_to_radian(FOV / 2)));
	data->slice_height = ceil((64 / data->distance) * data->dist_plane);
	if (data->slice_height > WINDOW_HEIGHT)
		data->slice_height = WINDOW_HEIGHT - 1;
	data->dist_before_wall = data->center - (data->slice_height / 2);
	y = -1;
	w = -1;
	while (++y < floor(data->dist_before_wall))
		my_mlx_pixel_put(data, x, y, rgb_to_int(data->ceiling));
	while (++w <= data->slice_height && w + y < WINDOW_HEIGHT)
		draw_texture(data, x, w + y);
	while (++w + y < WINDOW_HEIGHT)
		my_mlx_pixel_put(data, x, w + y, rgb_to_int(data->floor));
}

