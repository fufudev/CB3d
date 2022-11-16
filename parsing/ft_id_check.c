/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_id_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:16:00 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/14 12:21:35 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_id_is_true_part_2(char *str, t_data *data)
{
	if (ft_strncmp(str, "F ", 2) == 0 && data->f == 0)
	{
		data->f = 1;
		ft_check_rgb(&str[2], data);
		return (1);
	}
	if (ft_strncmp(str, "C ", 2) == 0 && data->c == 0)
	{
		data->c = 1;
		ft_check_rgb(&str[2], data);
		return (1);
	}
	return (0);
}

char	*get_txt_name(char *str)
{
	int	i;
	int begin;
	char *filename;

	i = 0;
	while (str[i++])
	{
		if (ft_is_whitespace(str[i]) == 1 || str[i] == '/' || str[i] == '.')
			continue ;
		else
			break ;
	}
	begin = i - 1;
	if (ft_is_whitespace(str[i]) != 1)
	{
		while (str[i] && ft_is_whitespace(str[i]) == 0)
			i++;
	}
	filename = malloc(i - begin + 1);
	ft_strlcpy(filename, &str[begin], i + 1);
	return (filename);
}

int	txt(char *str, int text, t_data *data)
{
	char	*filename;

	filename = get_txt_name(str);
	if (open(filename, O_RDONLY) == -1)
		free_map_file(data, data->map, "Error\nTexture not valid\n");
	if (text == 0)
		data->f_no = filename;
	if (text == 1)
		data->f_so = filename;
	if (text == 2)
		data->f_we = filename;
	if (text == 3)
		data->f_ea = filename;
	return (1);
}

int	ft_id_is_true(char *str, t_data *d)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && d->no == 0)
	{
		d->no = 1;
		return (ft_path(&str[3], d) && txt(&str[3], 0, d));
	}
	else if (ft_strncmp(str, "SO ", 3) == 0 && d->so == 0)
	{
		d->so = 1;
		return (ft_path(&str[3], d) && txt(&str[3], 1, d));
	}
	else if (ft_strncmp(str, "WE ", 3) == 0 && d->we == 0)
	{
		d->we = 1;
		return (ft_path(&str[3], d) && txt(&str[3], 2, d));
	}
	else if (ft_strncmp(str, "EA ", 3) == 0 && d->ea == 0)
	{
		d->ea = 1;
		return (ft_path(&str[3], d) && txt(&str[3], 3, d));
	}
	if (ft_id_is_true_part_2(str, d) == 1)
		return (1);
	free_map_file(d, d->map, "Error\nCheck the ID in the map.\n");
	return (0);
}

void	ft_check_id(t_data *data)
{
	int	i;
	int	good_value;
	int	indic;

	init_value(data, &i, &good_value, &indic);
	while (data->map[i])
	{
		indic = ft_parse_id(data->map[i++], data);
		if (indic == 1)
		{
			if (good_value != 6)
				free_map_file(data, data->map, "Error\nMap incorrect.\n");
			else
			{
				ft_check_map(&(data->map[i - 1]), data);
				break ;
			}
		}
		if (indic == 0)
			good_value++;
	}
	if (data->indic == 0)
		free_map_file(data, data->map, "Error\nCan't found a player.\n");
}
