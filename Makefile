# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:20:30 by gialexan          #+#    #+#              #
#    Updated: 2023/02/28 23:36:50 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definições de variáveis

NAME = minishell

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SOURCES_FILES = main.c			\
				scanner.c		\
				scanner_utils.c	\
				parser.c		\
				parser_utils.c	\
				parser_type.c   \
				linkedlist.c

SOURCES_BASE = src
VPATH = $(SOURCES_BASE)			\
		$(SOURCES_BASE)/scanner	\
		$(SOURCES_BASE)/parser	\
		$(SOURCES_BASE)/helper

OBJ_DIR = obj
INCLUDES = -I./include

INC_BASE = include
HEADERS =	$(INC_BASE)/minishell.h \
			$(INC_BASE)/scanner.h	\
			$(INC_BASE)/parser.h	\
			$(INC_BASE)/helper.h

OBJECTS = $(SOURCES_FILES:%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -g $(INCLUDES)

RM = rm -rf

# Regras do Makefile

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

run:
	valgrind ./minishell

.PHONY: all clean fclean re