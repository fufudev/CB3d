#include "../cub3d.h"

int	check_hz_broke(t_data *data)
{
	if ((floor(data->hz.tx / 64.0) <= 0) || (floor(data->hz.tx / 64.0) > ft_biglen(data->s_map) - 1))
		return (1);
	if ((size_t)(floor(data->hz.ty / 64) <= ft_strlen2d(data->s_map) - 1))
	{
		if ((size_t)(floor(data->hz.tx / 64.0) >= ft_strlen(data->s_map[(int)(floor(data->hz.ty / 64))] - 1)))
			return (1);
	}
	return (0);
}

int	check_vt_broke(t_data *data)
{
	if (!(floor(data->vt.ty / 64.0) >= 0 && floor(data->vt.ty / 64.0) < ft_strlen2d(data->s_map) - 1))
		return (1);
	return (0);
}

double	degree_to_radian(double r)
{
	return((r * (M_PI / 180)) + 0.001);
}

int	ft_biglen(char **s)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
			j++;
		if (j > len)
			len = j;
		i++;
	}
	return (len);
}

void	remove_distorsion(t_data *data)
{
	//if (data->tmp_angle >= data->player_angle)
	//{
	//	data->distance = data->distance
	//		* cos(degree_to_radian(data->tmp_angle - data->player_angle));
	//}
	//else
	//{
		data->distance = data->distance
			* cos(degree_to_radian(data->player_angle - data->tmp_angle));
	//}
}
