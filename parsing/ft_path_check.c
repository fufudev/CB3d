/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:04 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:39:00 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_path_rest(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_is_whitespace(str[i]) == 1))
			ft_msg_free(data->map, "Error\nSomehing went wrong after path.\n");
	}
}

void	ft_check_xpm(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i] != 'm' && str[i] != 'M')
		ft_msg_free(data->map, "Error\nPath not a xpm file.\n");
	if (str[i - 1] != 'p' && str[i - 1] != 'P')
		ft_msg_free(data->map, "Error\nPath not a xpm file.\n");
	if (str[i - 2] != 'x' && str[i - 2] != 'X')
		ft_msg_free(data->map, "Error\nPath not a xpm file.\n");
	if (str[i - 3] != '.')
		ft_msg_free(data->map, "Error\nPath not a xpm file.\n");
}

int	ft_path(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_is_whitespace(str[i]) == 1)
			continue ;
		else
			break ;
	}
	if (ft_is_whitespace(str[i]) != 1)
	{
		if (str[i] == '\0')
			ft_msg_free(data->map, "Error\nPath not a xpm file.\n");
		while (str[i] && ft_is_whitespace(str[i]) == 0)
			i++;
		if (ft_is_whitespace(str[i]) == 1)
			ft_path_rest(&str[i], data);
	}
	i--;
	ft_check_xpm(&str[i], data);
	return (1);
}

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

void	ft_putstr_fd(char *msg, int fd)
{
	write(fd, msg, ft_strlen(msg));
}