/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_id_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:16:00 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:28:41 by ffiliz           ###   ########.fr       */
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

int	ft_id_is_true(char *str, t_data *data)
{
	if (ft_strncmp(str, "NO ", 3) == 0 && data->no == 0)
	{
		data->no = 1;
		return (ft_path(&str[3], data));
	}
	else if (ft_strncmp(str, "SO ", 3) == 0 && data->so == 0)
	{
		data->so = 1;
		return (ft_path(&str[3], data));
	}
	else if (ft_strncmp(str, "WE ", 3) == 0 && data->we == 0)
	{
		data->we = 1;
		return (ft_path(&str[3], data));
	}
	else if (ft_strncmp(str, "EA ", 3) == 0 && data->ea == 0)
	{
		data->ea = 1;
		return (ft_path(&str[3], data));
	}
	if (ft_id_is_true_part_2(str, data) == 1)
		return (1);
	ft_msg_free(data->map, "Error\nMap false.\n");
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
