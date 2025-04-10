# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/04/10 16:03:48 by ctommasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./includes
CFLAGS_BONUS = -Wall -Wextra -Werror -I ./includes `pkg-config --cflags sdl2`
HEADERS = -I ./MLX42/include
RM	= rm -rf
MAKEFLAGS = --no-print-directory
SDL = `pkg-config --cflags --libs sdl2`


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
		./src/game/keypress.c ./src/game/draw.c ./src/game/raycasting.c \
		./src/game/textures.c ./src/game/move_player.c \

SRCS_BONUS = ./src_bonus/main_bonus/main_bonus.c ./src_bonus/main_bonus/error_bonus.c \
		./src_bonus/init_bonus/init_variables_bonus.c ./src_bonus/init_bonus/init_map_bonus.c ./src_bonus/init_bonus/init_game_bonus.c \
		./src_bonus/utils_bonus/check_args_bonus.c  ./src_bonus/utils_bonus/init_map_utils_bonus.c  ./src_bonus/utils_bonus/save_map_utils_bonus.c \
		./src_bonus/game_bonus/keypress_bonus.c ./src_bonus/game_bonus/draw_bonus.c ./src_bonus/game_bonus/raycasting_bonus.c ./src_bonus/game_bonus/minimap_bonus.c \
		./src_bonus/game_bonus/textures_bonus.c ./src_bonus/game_bonus/move_player_bonus.c \
		./src_bonus/game_bonus/draw_map_bonus.c ./src_bonus/utils_bonus/draw_utils_bonus.c ./src_bonus/game_bonus/draw_door_bonus.c \
		./src_bonus/object_bonus/draw_object_bonus.c ./src_bonus/object_bonus/object_utils_bonus.c ./src_bonus/object_bonus/pick_up_object_bonus.c \
		./src_bonus/init_bonus/init_variables2_bonus.c ./src_bonus/game_bonus/sounds_bonus.c

# Archivos objeto
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

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
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo -n "\r                                                                            \r"
	@echo "[$(GREEN)DONE$(RESET)] Linking complete: [$(MAGENTA)$(NAME)$(RESET)] - Complete!"

bonus_pro: CFLAGS += -D MANDATORY=0
bonus_pro: $(NAME_BONUS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS_BONUS) $(OBJS_BONUS) $(LIBFT) $(MLX) $(SDL) -lSDL2 -lpthread -o $(NAME_BONUS)
	@echo -n "\r                                                                            \r"
	@echo "[$(GREEN)DONE$(RESET)] Linking complete: [$(MAGENTA)$(NAME_BONUS)$(RESET)] - Complete!"

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "[$(RED)DELETED$(RESET)] Object files [$(RED)*.o$(RESET)] - Cleaned!"

fclean:
	@$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)
	@echo "[$(RED)DELETED$(RESET)] Cub3D file [$(RED)$(NAME)$(RESET)] - Cleaned!"

re: fclean all

.PHONY:	all clean fclean re libmlx

.SILENT: