# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:20:30 by gialexan          #+#    #+#              #
#    Updated: 2023/04/07 16:50:10 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definições de variáveis

NAME = minishell

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SOURCES_FILES = main.c				\
				scanner.c			\
				scanner_utils.c		\
				parser.c			\
				parser_utils.c		\
				parser_type.c   	\
				redirect.c			\
				redirect_utils.c	\
				expansion.c 		\
				expansion_utils.c 	\
				environment.c   	\
				interface.c 		\
				builtins.c 			\
				export.c 			\
				unset.c 			\
				echo.c 				\
				exit.c 				\
				pwd.c 				\
				env.c 				\
				cd.c 				\
				exit_utils.c 		\
				exec_utils.c 		\
				cleaner.c 			\
				print.c 			\
				error.c				\
				path.c				\
				exec.c 				\
				exec_cmd.c 				
				

SOURCES_BASE = src
VPATH = $(SOURCES_BASE)				\
		$(SOURCES_BASE)/scanner		\
		$(SOURCES_BASE)/parser		\
		$(SOURCES_BASE)/exec		\
		$(SOURCES_BASE)/helper		\
		$(SOURCES_BASE)/builtins 	\
		$(SOURCES_BASE)/expansion 	\
		$(SOURCES_BASE)/env 		

OBJ_DIR = obj
INCLUDES = -I./include

INC_BASE = include
HEADERS =	$(INC_BASE)/minishell.h \
			$(INC_BASE)/scanner.h	\
			$(INC_BASE)/parser.h	\
			$(INC_BASE)/execute.h	\
			$(INC_BASE)/helper.h 	\
			$(INC_BASE)/builtins.h 	

OBJECTS = $(SOURCES_FILES:%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -g $(INCLUDES)
READLINE = -lreadline
RM = rm -rf

# Regras do Makefile

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_PATH)

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

run: $(NAME)
	valgrind --suppressions=readline.supp --track-fds=yes  --leak-check=full --trace-children-skip='/bin/,/sbin/' \
                    --track-origins=yes --show-leak-kinds=all ./$(NAME)
				
#--track-origins=yes 						-> valores não inicializados.					
#--trace-children-skip='/bin/,/sbin/' 		-> elimina os binário.
#--trace-children=yes 						-> processo filho.
#--leak-check=full --show-leak-kinds=all 	-> tudp que é tipo de leak.
#valgrind --track-fds=yes 					-> descritores de arq.
.PHONY: all clean fclean re