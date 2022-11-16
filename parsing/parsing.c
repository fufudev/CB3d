/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:37:03 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:37:57 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
		ft_msg("Error\nArgument bigger than 2.\n");
	if (i < 2)
		ft_msg("Error\nYou need a map for this program.\n");
}

void	ft_name(char *argv)
{
	int	i;

	i = ft_strlen(argv) - 1;
	if (argv[i] != 'b')
		ft_msg("Error\nExtension of the file is incorrect\n");
	if (argv[i - 1] != 'u')
		ft_msg("Error\nExtension of the file is incorrect\n");
	if (argv[i - 2] != 'c')
		ft_msg("Error\nExtension of the file is incorrect\n");
	if (argv[i - 3] != '.')
		ft_msg("Error\nExtension of the file is incorrect\n");
}

void	ft_check_file(t_parsing *parse, char **argv)
{
	ft_name(argv[1]);
	parse->fd = open(argv[1], O_DIRECTORY);
	if (parse->fd > 0)
		ft_msg("Error\nYour map can't be a directory.\n");
	else
	{
		parse->fd = open(argv[1], O_RDONLY);
		if (parse->fd < 0)
			ft_msg("Error\nFile incorrect\n");
	}
}

int	parse_digit(char *str, t_data *data)
{
	int		i;
	char	*tmp;
	int		tmp_atoi;

	tmp = NULL;
	i = 0;
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (i > 3)
		ft_msg_free(data->map, "Error\nRGB false\n");
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, &str[0], 4);
	tmp_atoi = ft_atoi(tmp);
	free(tmp);
	ft_check_value(tmp_atoi, data);
	return (i - 1);
}

int	ft_parse_id(char *map, t_data *data)
{
	int	i;
	int	indic;

	i = -1;
	indic = 0;
	while (map[++i])
	{
		if (ft_is_whitespace(map[i]) == 1)
			continue ;
		if (ft_isalpha(map[i]) == 1)
		{
			indic++;
			ft_id_is_true(&map[i], data);
			break ;
		}
		if (ft_isdigit(map[i]) == 1)
			return (1);
	}
	if (indic == 0)
		return (2);
	return (0);
}
