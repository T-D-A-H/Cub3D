# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 13:05:04 by jaimesan          #+#    #+#              #
#    Updated: 2025/04/02 13:27:25 by ctommasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_b

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./includes
HEADERS = -I ./MLX42/include
RM	= rm -rf
MAKEFLAGS = --no-print-directory

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)/libmlx.a -lXext -lX11 -lm -lz

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m
YELLOW := \033[33m
CYAN := \033[36m
MAGENTA := \033[35m
BLUE := \033[34m

# Archivos fuente
SRCS =	./src/main/main.c ./src/main/error.c \
		./src/init/init_variables.c ./src/init/init_map.c ./src/init/init_game.c \
		./src/utils/check_args.c  ./src/utils/init_map_utils.c  ./src/utils/save_map_utils.c \
		./src/game/keypress.c ./src/game/draw.c ./src/game/raycasting.c ./src/game/minimap.c \
		./src/utils/delete_after.c ./src/game/textures.c ./src/game/move_player.c \
		./src/game/draw_map.c ./src/game/door.c ./src/game/render_objects.c
		
# Archivos objeto
OBJS = $(SRCS:.c=.o)

all: $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@make -sC $(MLX_DIR)

%.o: %.c
	@echo -n "\r                                                                            \r"
	@echo -n "[$(GREEN)DONE$(RESET)] Compiling: [$(YELLOW)$<$(RESET)]\r"
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< 

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo -n "\r                                                                            \r"
	@echo "[$(GREEN)DONE$(RESET)] Linking complete: [$(MAGENTA)$(NAME)$(RESET)] - Complete!"

bonus: CFLAGS += -D BONUS=1
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -o $(NAME_BONUS)
	@echo -n "\r                                                                            \r"
	@echo "[$(GREEN)DONE$(RESET)] Linking complete: [$(MAGENTA)$(NAME_BONUS)$(RESET)] - Complete!"

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "[$(RED)DELETED$(RESET)] Object files [$(RED)*.o$(RESET)] - Cleaned!"

fclean:
	@$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(NAME) $(NAME_BONUS)
	@echo "[$(RED)DELETED$(RESET)] Cub3D file [$(RED)$(NAME)$(RESET)] - Cleaned!"

re: fclean all

.PHONY:	all clean fclean re libmlx

.SILENT: