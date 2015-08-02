# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 01:49:54 by amaurer           #+#    #+#              #
#    Updated: 2015/05/03 21:38:00 by amaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	src/
OBJ_DIR		=	build/
INC_DIR		=	include libft/includes glfw/include SOIL/src
BIN_DIR		=	bin/

NAME		=	arkanoid
BIN_NAME	=	$(BIN_DIR)$(NAME)
SRC_FILES	=	main.c \
				core/actions/actions.c \
				core/player.c \
				core/game.c \
				core/balls.c \
				core/bonus.c \
				core/bonus2.c \
				core/update.c \
				core/update2.c \
				core/menu.c \
				core/parse.c \
				core/init.c \
				gfx/glfw.c \
				gfx/callbacks.c \
				gfx/draw_game.c \
				gfx/draw_game2.c \
				gfx/draw_game3.c \
				gfx/draw_menu.c \
				util.c \
				util2.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

CC			=	clang
CC_FLAGS	=	-Wall -Werror -Wextra -g3
CC_LIBS		=	-lft -Llibft -Lglfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -LSOIL/lib -lSOIL

all: SOIL/lib/libSOIL.a glfw/src/libglfw3.a libft  $(BIN_NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

$(BIN_NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_NAME) $(CC_LIBS) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(subst $() $(), -I, $(INC_DIR)) -o $@ -c $<

clean:
	make -C libft clean
	# make -C glfw clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C libft fclean
	rm -rf $(BIN_NAME)

re: fclean all

SOIL/lib/libSOIL.a:
	mkdir SOIL/projects/makefile/obj
	mkdir SOIL/lib
	@make -C SOIL/projects/makefile

libft:
	@make -C libft

glfw/src/libglfw3.a:
	git submodule init
	git submodule update
	cd glfw; cmake .
	make -C glfw

.PHONY: all re fclean clean libft