/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:53:19 by anggonza          #+#    #+#             */
/*   Updated: 2022/11/23 10:38:59 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_opengl.h"
# include <math.h>

# define ESC 0x35
# define FOV 60
# define DOWN -1
# define UP 1
# define EAST 0
# define WEST 180
# define NORTH 90
# define SOUTH 270
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define LEFT_L 65361
# define RIGHT_L 65363
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

typedef struct s_point
{
	double	xa;
	double	ya;
	double	ay;
	double	ax;
	double	tx;
	double	ty;
}	t_point;

typedef struct s_data
{
	char	**map;
	char	**s_map;
	int		ceiling[3];
	int		floor[3];
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		indic;
	int		newline;
	int		pos_y;
	int		pos_x;
	double	player_y;
	double	player_x;
	double	player_angle;
	double	tmp_angle;
	double	distance;
	double	line_height;
	double	slice_height;
	double	center;
	double	dist_plane;
	double	dist_before_wall;
	int		orientation;
	int		speed;
	int		offset;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		big_len;
	int		txt_x;
	int		txt_y;
	int		index;
	size_t	len;
	t_point	vt;
	t_point	hz;
	char	*f_no;
	char	*f_so;
	char	*f_we;
	char	*f_ea;
	int		*a_no;
	int		*a_so;
	int		*a_we;
	int		*a_ea;
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
}	t_data;

typedef struct s_parsing
{
	int	fd;
	int	indic;
}	t_parsing;

int		txt(char *str, int text, t_data *data);
void	find_and_draw(t_data *data);
void	window(t_data *data);
void	draw_rayon(t_data *data, double wall_x, double wall_y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_putstr_fd(char *msg, int fd);
void	ft_msg(char *msg);
void	ft_msg_free(char **map2, char *msg);
void	ft_check_file(t_parsing *parse, char **argv);
void	ft_check_argument(char **argv);
void	ft_name(char *argv);
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_read_map(t_data *data, t_parsing *parse);
void	start_parsing(t_data *data, t_parsing *parse, char **argv);
void	ft_check_id(t_data *data);
int		ft_parse_id(char *map, t_data *data);
int		ft_is_whitespace(char c);
int		ft_is_whitespace(char c);
int		ft_id_is_true(char *str, t_data *data);
int		ft_id_is_true_part_2(char *str, t_data *data);
void	init_id(t_data *data);
void	ft_path_rest(char *str, t_data *data);
void	ft_check_xpm(char *str, t_data *data);
int		ft_path(char *str, t_data *data);
void	ft_check_rgb(char *str, t_data *data);
int		parse_digit(char *str, t_data *data);
void	ft_check_value(int tmp_atoi, t_data *data);
void	ft_check_map(char **map, t_data *data);
int		ft_check_wall(char *map, int i, t_data *data);
int		ft_check_line(char **map, int i, int j, t_data *data);
void	ft_check_first_line(char *map, t_data *data);
void	ft_check_around(char **map, int i, int j, t_data *data);
void	ft_check_newline( char *map, t_data *data);
void	ft_check_zero(char **map, int i, int j, t_data *data);
void	ft_check_endline(char **map, t_data *data);
void	ft_replace_space_by_one(t_data *data);
void	check_overflow_map(t_data *data, int i, int j);
void	ft_freesplit(char **str);
size_t	ft_strlen2d(char **s);
int		ft_strlen_int(const char *s);
void	ft_check_first_last(int i, char **map, t_data *data);
int		ft_check_middle(int i, int j, char **map, t_data *data);
void	ft_swoosh(int *swoosh, char c, int *i);
int		ft_wall_exist(char *s);
void	init_value(t_data *data, int *i, int *good_value, int *indic);
void	draw_player(t_data *data, int py, int px, int color);
void	draw_rect(t_data *data, int x, int y, int color);
int		is_player(char c);
void	draw_map(char **map, t_data *data);
void	escape(t_data *data);
void	quit(t_data *data);
int		closewd(t_data *data);
void	init_value_pos(t_data *data);
double	degree_to_radian(double degree);
int		draw_again(t_data *data);
void	finding_wall(t_data *data);
void	find_horizontal_intersection(t_data *data);
void	find_vertical_intersection(t_data *data);
void	draw_3d(t_data *data, int x);
void	draw_column(t_data *data, int x);
void	find_and_draw(t_data *data);
void	find_distance(t_data *data);
void	window(t_data *data);
void	start_display(t_data *data);
void	draw_column(t_data *data, int x);
void	event(t_data *data);
void	find_and_draw(t_data *data);
int		key_hook(int keycode, t_data *data);
void	step_side(int keycode, t_data *data);
void	right_side(t_data *data, double *x_tmp, double *y_tmp);
void	left_side(t_data *data, double *x_tmp, double *y_tmp);
void	up_back(int keycode, t_data *data);
void	back(t_data *data, double *x_tmp, double *y_tmp);
void	up(t_data *data, double *x_tmp, double *y_tmp);
void	left_right(int keycode, t_data *data);
void	find_distance(t_data *data);
void	save_distance(t_data *data, double x, double y, int orientation);
void	draw_rayon(t_data *data, double wall_x, double wall_y);
void	find_vertical_intersection(t_data *data);
void	find_horizontal_intersection(t_data *data);
int		check_vt_broke(t_data *data);
int		check_hz_broke(t_data *data);
int		ft_biglen(char **s);
void	init_coordinates_vertical(t_data *data, double *xa, double *ax);
void	init_coordinates_horizontal(t_data *data, double *ya, double *ay);
double	degree_to_radian(double r);
void	get_color(t_data *data, int x, int y, int orientation);
int		rgb_to_int(int *tab);
void	fov_3d(t_data *data);
void	remove_distorsion(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_check_middle(int i, int j, char **map, t_data *data);
void	ft_check_first_last(int i, char **map, t_data *data);
int		is_player(char c);
void	ft_save_data(t_data *data);
void	ft_save_c(char *s, t_data *data);
void	ft_save_f(char *s, t_data *data);
int		ft_save(char *s, t_data *data, int indic, int array);
void	init_img_addr(t_data *data);
void	free_img_filename(t_data *data);
int		check_left_distance(t_data *data, double x_tmp, double y_tmp);
int		check_right_distance(t_data *data, double x_tmp, double y_tmp);
int		check_up_distance(t_data *data, double x_tmp, double y_tmp);
int		check_back_distance(t_data *data, double x_tmp, double y_tmp);
void	free_map_file(t_data *data, char **map, char *msg);
void	init_positionn(t_data *data, int i, int j);
#endif
