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
