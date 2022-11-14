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

void	ft_check_rgb(char *str, t_data *data)
{
	int	i;
	int	indic;
	int	swoosh;

	i = -1;
	indic = 0;
	swoosh = 0;
	while (str[++i])
	{
		ft_swoosh(&swoosh, str[i], &i);
		if (ft_is_whitespace(str[i]) == 1)
			continue ;
		if (indic < 3 && ft_isdigit(str[i]) == 1)
		{
			if (swoosh != 0)
				ft_msg_free(data->map, "Error\nPb 1 RGB\n.");
			i = i + parse_digit(&str[i], data);
			indic++;
			swoosh = 1;
		}
		else
			ft_msg_free(data->map, "Error\nProblem 2 RGB\n");
	}
	if (indic != 3)
		ft_msg_free(data->map, "Error\nRGB not good\n");
}

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

char	*get_txt_name(char *str, t_data *data)
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
	char *filename;

	filename = get_txt_name(str, data);
	if (open(filename, O_RDONLY) == -1)
		ft_msg_free(data->map, "Error\nTexture not valid\n");
	if (text == 0)
		data->name_no = filename;
	if (text == 1)
		data->name_so = filename;
	if (text == 2)
		data->name_we = filename;
	if (text == 3)
		data->name_ea = filename;
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
	ft_msg_free(d->map, "Error\nCheck the ID in the map.\n");
	return (0);
}

void	ft_check_id(t_data *data, t_parsing *parse)
{
	int	i;
	int	good_value;
	int	indic;

	init_value(&i, &good_value, &indic);
	init_id(data);
	while (data->map[i])
	{
		indic = ft_parse_id(data->map[i++], data);
		if (indic == 1)
		{
			if (good_value != 6)
				ft_msg_free(data->map, "Error\nMap incorrect.\n");
			else
			{
				ft_check_map(&(data->map[i - 1]), data, parse);
				break ;
			}
		}
		if (indic == 0)
			good_value++;
	}
	if (data->indic == 0)
		ft_msg_free(data->map, "Error\nCan't found a player.\n");
}
