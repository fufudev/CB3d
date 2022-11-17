/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:57:48 by ffiliz            #+#    #+#             */
/*   Updated: 2022/11/17 21:59:47 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_save(char *s, t_data *data, int indic, int array)
{
	int		i;
	int		nb;
	char	*tmp;
	int		tmp_atoi;

	i = -1;
	nb = 1;
	while (s[++i])
	{
		if (ft_isdigit(s[i]) == 1)
			nb++;
		if (s[i] == ',' || (array == 2 && (i == ft_strlen_int(s) - 1)))
		{
			tmp = malloc(sizeof(char) * nb);
			ft_strlcpy(tmp, s, nb);
			tmp_atoi = ft_atoi(tmp);
			free(tmp);
			if (indic == 1)
				data->ceiling[array] = tmp_atoi;
			if (indic == 0)
				data->floor[array] = tmp_atoi;
			return (nb);
		}
	}
	return (nb);
}

void	ft_save_f(char *s, t_data *data)
{
	int	i;
	int	array;

	i = 0;
	array = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 1)
		{
			i = i + ft_save(&s[i], data, 0, array);
			array++;
			if (i > ft_strlen_int(s) - 1)
				return ;
			continue ;
		}
		i++;
	}
}

void	ft_save_c(char *s, t_data *data)
{
	int	i;
	int	array;

	i = 0;
	array = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 1)
		{
			i = i + ft_save(&s[i], data, 1, array);
			array++;
			if (i > ft_strlen_int(s) - 1)
				return ;
			continue ;
		}
		i++;
	}
}

void	ft_save_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (ft_isalpha(data->map[i][j]) == 1)
			{
				if (ft_strncmp(&data->map[i][j], "F", 1) == 0)
					ft_save_f(data->map[i], data);
				if (ft_strncmp(&data->map[i][j], "C", 1) == 0)
					ft_save_c(data->map[i], data);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	save_distance(t_data *data, double x, double y, int orientation)
{
	data->pos_x = x;
	data->pos_y = y;
	data->orientation = orientation;
}
