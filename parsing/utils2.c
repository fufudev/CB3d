/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:36:36 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/17 22:03:57 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_freesplit(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = (char *) NULL;
		i++;
	}
	free(str);
	str = (char **) NULL;
}

size_t	ft_strlen2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	escape(t_data *data)
{
	ft_freesplit(data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(1);
}

void	quit(t_data *data)
{
	ft_freesplit(data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(1);
}

int	closewd(t_data *data)
{
	quit(data);
	return (0);
}
