/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:34:25 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/17 19:40:13 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_coords__horizontal(t_data *data, double *ya, double *ay)
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

void	init_coords__vertical(t_data *data, double *xa, double *ax)
{
	if ((data->tmp_angle >= 0.0 && data->tmp_angle <= 90.0)
		|| (data->tmp_angle >= 270.0 && data->tmp_angle <= 360.0))
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

void	init_value(t_data *data, int *i, int *good_value, int *indic)
{
	*i = 0;
	*indic = 0;
	*good_value = 0;
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->player_y = 0;
	data->player_x = 0;
	data->slice_height = 0;
	data->speed = 20;
	data->f_no = NULL;
	data->f_so = NULL;
	data->f_we = NULL;
	data->f_ea = NULL;
}

void	init_img_addr(t_data *data)
{
	data->no_img.addr = mlx_get_data_addr(data->no_img.img, &data->no_img.bpp,
			&data->no_img.line, &data->no_img.endian);
	data->so_img.addr = mlx_get_data_addr(data->so_img.img, &data->so_img.bpp,
			&data->so_img.line, &data->so_img.endian);
	data->we_img.addr = mlx_get_data_addr(data->we_img.img, &data->we_img.bpp,
			&data->we_img.line, &data->we_img.endian);
	data->ea_img.addr = mlx_get_data_addr(data->ea_img.img, &data->ea_img.bpp,
			&data->ea_img.line, &data->ea_img.endian);
}

void	init_img(t_data *data)
{
	int	width;
	int	height;

	data->no_img.img = mlx_xpm_file_to_image(data->mlx_ptr, data->f_no,
			&width, &height);
	if (!data->no_img.img)
		free_map_file(data, data->map, "Error\nProbleme xpm file to img\n");
	data->so_img.img = mlx_xpm_file_to_image(data->mlx_ptr, data->f_so,
			&width, &height);
	if (!data->so_img.img)
		free_map_file(data, data->map, "Error\nProbleme xpm file to img\n");
	data->we_img.img = mlx_xpm_file_to_image(data->mlx_ptr, data->f_we,
			&width, &height);
	if (!data->we_img.img)
		free_map_file(data, data->map, "Error\nProbleme xpm file to img\n");
	data->ea_img.img = mlx_xpm_file_to_image(data->mlx_ptr, data->f_ea,
			&width, &height);
	if (!data->ea_img.img)
		free_map_file(data, data->map, "Error\nProbleme xpm file to img\n");
	free_img_filename(data);
	init_img_addr(data);
}
