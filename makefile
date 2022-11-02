CC	= gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LDFLAG = -Lmlx -framework OpenGL -framework AppKit 
NAME = cub3d
I_DIR = include
L_FT = libft

SRC =	parsing.c		\
		main.c			\
		utils.c			\
		utils2.c		\
		ft_check.c		\
		map.c			\
		ft_id_check.c	\
		ft_id_check_2.c	\
		ft_path_check.c \
		ft_init.c		\

OBJ = $(SRC:%.c=%.o)

all: cub3d.h $(NAME)

$(NAME): $(L_FT)/libft.a $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -I$(I_DIR) -L$(L_FT) libft/libft.a mlx/libmlx.a -o $(NAME)

$(L_FT)/libft.a:
	make -C $(L_FT) 

%.o: %.c
	$(CC) -g -o  $@ -c $< -I$(I_DIR)

clean:
	make clean -C $(L_FT)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(L_FT)
	rm  -rf $(NAME)

re: fclean all

.PHONY: all run clean fclean re make_libft
