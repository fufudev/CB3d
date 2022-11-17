# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 22:22:05 by ffiliz            #+#    #+#              #
#    Updated: 2021/12/23 19:55:19 by ffiliz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra
NAME		=	libft.a
OBJ_DIR		=	obj
I_DIR		=	.

SRC			=	${wildcard *.c}	

SRC_BONUS = $(SRC)	\
				
ifdef WITH_BONUS
	OBJ				=	$(SRC_BONUS:%.c=%.o)
	OBJ_PFX			=	$(addprefix $(OBJ_DIR)/, $(OBJ))
else
	OBJ				=	$(SRC:%.c=%.o)
	OBJ_PFX			=	$(addprefix $(OBJ_DIR)/, $(OBJ))
endif

all: $(NAME)

$(NAME): $(OBJ_PFX)
	ar -rcs $(NAME) $(OBJ_PFX)

bonus:
	@make WITH_BONUS=1 all 

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(I_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
