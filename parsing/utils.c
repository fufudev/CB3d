/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:35:57 by ffiliz            #+#    #+#             */
/*   Updated: 2022/07/15 11:36:27 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	j;
	size_t	i;
	char	*pt;

	if (!s2)
		return (s1);
	if (!s1)
		s1 = ft_calloc(1, 1);
	i = -1;
	j = -1;
	pt = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (pt == NULL)
		return (NULL);
	while (s1[++i])
		pt[i] = s1[i];
	while (s2[++j])
		pt[i + j] = s2[j];
	pt[i + j] = '\0';
	free(s1);
	return (pt);
}

int	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	free_img_filename(t_data *data)
{
	free(data->f_no);
	free(data->f_ea);
	free(data->f_we);
	free(data->f_so);
	data->f_no = NULL;
	data->f_so = NULL;
	data->f_we = NULL;
	data->f_ea = NULL;
}

void	ft_msg_free(char **map, char *msg)
{
	ft_freesplit(map);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	free_map_file(t_data *data, char **map, char *msg)
{
	ft_freesplit(map);
	ft_putstr_fd(msg, 2);
	if (data->f_ea)
		free(data->f_ea);
	if (data->f_we)
		free(data->f_we);
	if (data->f_so)
		free(data->f_so);
	if (data->f_no)
		free(data->f_no);
	exit(EXIT_FAILURE);
}

void	ft_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
