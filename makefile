CC	= gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAG = -Lmlx -framework OpenGL -framework AppKit
#LDFLAG = -Lmlx_linux
NAME = cub3d
#I_DIR = /usr/include -lXext -lX11 -lm -lz
I_DIR = include
L_FT = libft
#MLX = mlx_linux
MLX = mlx
SRC =	parsing/parsing.c	    	\
		main.c			        	\
		parsing/utils.c				\
		parsing/utils2.c			\
		parsing/utils3.c			\
		parsing/ft_check.c			\
		parsing/map.c				\
		parsing/ft_id_check.c		\
		parsing/ft_id_check_2.c		\
		parsing/ft_path_check.c		\
		display/ft_init.c			\
		display/utils_draw.c		\
		display/save.c				\
		display/moov.c				\
		display/moov_2.c			\
		display/moov_3.c			\
		display/display.c			\
		display/draw.c				\
		display/distance.c			\

OBJ = $(SRC:%.c=%.o)

all: cub3d.h $(NAME)

$(NAME): $(L_FT)/libft.a $(OBJ)
		$(CC) $(LDFLAG) $(CFLAGS) $(OBJ) -I$(I_DIR) -L$(L_FT) libft/libft.a $(MLX)/libmlx.a -o $(NAME)

$(L_FT)/libft.a:
	make -C $(L_FT)

%.o: %.c
	$(CC) $(CFLAGS) -o  $@ -c $< -I$(I_DIR)

clean:
	make clean -C $(L_FT)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(L_FT)
	rm  -rf $(NAME)

re: fclean all

.PHONY: all run clean fclean re make_libft
