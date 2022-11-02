/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:36:36 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:36:51 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_freesplit(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

size_t	ft_strlen2d(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*void	escape(t_minilibx *mnlx)
{
	int	mlx_destroy_window(void *mlx_ptr, void *win_ptr);
	exit(1);
}*/

void	quit(t_data *data)
{
	int	mlx_destroy_window(void *mlx_ptr, void *win_ptr);
	ft_freesplit(data->s_map);
	exit(1);
}

int	closewd(t_data *data)
{
	quit(data);
	return (0);
}