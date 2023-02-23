# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:20:30 by gialexan          #+#    #+#              #
#    Updated: 2023/02/23 12:10:09 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_PATH		=	./libft

LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES_FILES	=	main.c \
					scanner.c \
					scanner_utils.c

SOURCES_DIR		=	src

OBJ_DIR			=	obj

HEADERS			=	./include/minishell.h \
					./include/scanner.h

INCLUDES		=	-I./include

VPATH			=	src src/scanner

OBJECTS			=	$(SOURCES_FILES:%.c=$(OBJ_DIR)/%.o)

NAME			=	minishell

CC				=	gcc

RM				=	rm -rf

CFLAGS			=	-Wall -Wextra -Werror $(INCLUDES)

$(OBJ_DIR)/%.o:	%.c $(HEADERS) | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ_DIR) $(OBJECTS) $(HEADERS)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJ_DIR)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

.PHONY:			all clean fclean re libft