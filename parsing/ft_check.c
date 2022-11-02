/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:12:10 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:14:53 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_around(char **map, int i, int j, t_data *data)
{
	if (map[i + 1] && ft_strlen(map[i + 1])
		>= ft_strlen(map[i]) && i != ft_strlen2d(map))
		if (map[i + 1][j] != '1' && ft_is_whitespace(map[i + 1][j]) != 1)
			ft_msg_free(data->map, "Error\nMap not close 1.\n");
	if (map[i - 1] && ft_strlen(map[i - 1]) >= ft_strlen(map[i]) && i != 0)
		if (map[i - 1][j] != '1' && ft_is_whitespace(map[i - 1][j]) != 1)
			ft_msg_free(data->map, "Error\nMap not close 2.\n");
	if (map[i] && map[i][j + 1] && j != ft_strlen(map[i]))
		if (map[i][j + 1] != '1' && ft_is_whitespace(map[i][j + 1]) != 1)
			ft_msg_free(data->map, "Error\nMap not close 3.\n");
	if (map[i] && map[i][j - 1] && j != 0)
		if (map[i][j - 1] != '1' && ft_is_whitespace(map[i][j - 1]) != 1)
			ft_msg_free(data->map, "Error\nMap not close 4.\n");
}

void	ft_check_zero(char **map, int i, int j, t_data *data)
{
	if ((!map[i + 1]) || (!map[i + 1][j])
		|| ft_is_whitespace(map[i + 1][j]) == 1)
		ft_msg_free(data->map, "Error\nMap not close 5.\n");
	if (i != 0)
		if ((!map[i - 1]) || (!map[i - 1][j])
			|| ft_is_whitespace(map[i - 1][j]) == 1)
			ft_msg_free(data->map, "Error\nMap not close 6.\n");
	if (j != ft_strlen(map[i]))
		if ((!map[i]) || (!map[i][j + 1])
			|| ft_is_whitespace(map[i][j + 1]) == 1)
			ft_msg_free(data->map, "Error\nMap not close 7.\n");
	if (j != 0)
		if ((!map[i]) || (!map[i][j - 1])
			|| ft_is_whitespace(map[i][j - 1]) == 1)
			ft_msg_free(data->map, "Error\nMap not close 8.\n");
}

void	ft_check_first_line(char *map, t_data *data)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (ft_is_whitespace(map[i]) == 1)
			continue ;
		if (map[i] == '1')
			continue ;
		else
			ft_msg_free(data->map, "Error\nCheck the wall\n");
	}
	i = ft_strlen(map) - 1;
	while (i > 0)
	{
		if (ft_is_whitespace(map[i]) == 1)
			ft_msg_free(data->map, "Error\nCheck the wall 2.\n");
		if (map[i] == '1')
			break ;
		i--;
	}
}

int	ft_check_line(char **map, int i, int j, t_data *data)
{
	if ((map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'E' || map[i][j] == 'W') && data->indic == 0)
	{
		data->pos_y = i;
		data->pos_x = j;
		data->player_y = i * 64 + 32;
		data->player_x = j * 64 + 32;
		data->indic = 1;
		if (map[i][j] == 'N')
			data->player_angle = NORTH;
		if (map[i][j] == 'S')
			data->player_angle = SOUTH;
		if (map[i][j] == 'E')
			data->player_angle = EAST;
		if (map[i][j] == 'W')
			data->player_angle = WEST;
		return (0);
	}
	if (map[i][j] == '1')
		return (0);
	if (map[i][j] == '0')
	{
		ft_check_zero(map, i, j, data);
		return (0);
	}
	return (1);
}

void	ft_check_endline(char **map, t_data *data)
{
	if (data->newline != ft_strlen2d(map) - 1)
		ft_msg_free(data->map, "Error\nMap incorrect....\n");
}
