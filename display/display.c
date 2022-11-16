#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	event(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, key_hook, data); // CHANGEZ KEYPRESS KEYPRESSMASK par 2 et 0
	mlx_hook(data->win_ptr, 17, 0, closewd, data);
	mlx_loop(data->mlx_ptr);
}

void	fov_3d(t_data *data)
{
	int		x;

	x = 0;
	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
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
		data->tmp_angle = data->tmp_angle - 0.03125;
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	if (!data->win_ptr)
		ft_msg_free(data->map, "Error\nPB WINDOWS\n");
}

void	start_display(t_data *data)
{
	window(data);
	init_img_addr(data);
	fov_3d(data);
	//find_and_draw(data);
	event(data);
}