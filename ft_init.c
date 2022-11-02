/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:34:25 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 12:15:58 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_value(int *i, int *good_value, int *indic)
{
	*i = 0;
	*indic = 0;
	*good_value = 0;
}

void	init_id(t_data *data)
{
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->player_y = 0;
	data->player_x = 0;
}