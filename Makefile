# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:20:30 by gialexan          #+#    #+#              #
#    Updated: 2023/01/26 21:08:56 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 				lexer

SRC_FILE = 			main.c

SRC_DIR = 			src

LIBFT_DIR = 		libft

SRC = 				$(addprefix $(SRC_DIR)/, $(SRC_FILE))

SRC_OBJ = 			$(SRC:.c=.o)

LIBFT = 			./libft/libft.a

RM = 				rm -f

CFLAGS = 			-Wall -Wextra -Werror

CC = 				gcc -g

all:	$(NAME)

$(NAME):			$(LIBFT) $(SRC_OBJ)
					$(CC) $(CFLAGS) $(SRC_OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
					$(MAKE) -C $(LIBFT_DIR)

clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) $(SRC_OBJ)
					
fclean:				clean
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re libft