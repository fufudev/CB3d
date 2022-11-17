/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:35:08 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/17 19:42:00 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_newline(char *map, t_data *data)
{
	int	i;

	i = ft_strlen(map);
	data->newline = 0;
	while (i > 0 && map[i] != ',')
		i--;
	if (map[i] == ',')
	{
		while (map[i] && map[i] != '\n')
			i++;
		if (map[i] == '\n')
		{
			while (map[i] && map[i] != '1')
				i++;
			if (map[i] == '1')
			{
				while (map[i++])
				{
					if (map[i] == '\n')
						data->newline++;
				}
			}
		}
	}
}

void	ft_read_map(t_data *data, t_parsing *parse)
{
	int		r;
	char	buf[2];
	char	*line;

	line = NULL;
	r = 1;
	while (r == 1)
	{
		r = read(parse->fd, buf, 1);
		if (r == 0)
			break ;
		buf[r] = '\0';
		line = ft_strjoin_free(line, buf);
	}
	if (!line[0])
	{
		free(line);
		ft_msg("Error\nMap is empty.\n");
	}
	ft_check_newline(line, data);
	data->map = ft_split(line, '\n');
	free(line);
	close(parse->fd);
}

void	ft_check_map(char **map, t_data *data)
{
	int	i;
	int	j;
	int	wall;

	i = -1;
	data->indic = 0;
	ft_check_endline(map, data);
	data->s_map = map;
	while (map[++i])
	{
		j = -1;
		wall = 0;
		while (map[i][++j])
		{
			ft_check_first_last(i, map, data);
			if (ft_check_middle(i, j, map, data) == 1)
				continue ;
			if (i != 0 && i != (int)ft_strlen2d(map) - 1)
				if (ft_check_line(map, i, j, data) == 1)
					free_map_file(data, data->map, "Error\nWrong char.\n");
			if (wall == 0 && ft_check_wall(map[i], j, data) == 0)
				wall = 1;
		}
	}
}

int	ft_check_wall(char *map, int i, t_data *data)
{
	int	len;

	len = ft_strlen(map);
	if (map[i] != '1')
		free_map_file(data, data->map,
			"Error\nYou have space after the wall and nothing behind\n");
	if (map[len - 1] != '1')
		free_map_file(data, data->map,
			"Error\nYou have space after the wall and nothing behind\n");
	return (0);
}

int	ft_wall_exist(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '1')
			return (1);
		i++;
	}
	return (0);
}
