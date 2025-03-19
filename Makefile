# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 13:05:04 by jaimesan          #+#    #+#              #
#    Updated: 2025/03/19 15:35:28 by ctommasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

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
		./src/init/init_struct.c ./src/init/init_variables.c ./src/init/init_map.c ./src/init/init_window.c \
		./src/utils/check_args.c  ./src/utils/init_map_utils.c  ./src/utils/save_map.c \
		./src/game/player.c ./src/game/draw.c \
		./src/utils/delete_after.c 
		
# Archivos objeto
OBJS = $(SRCS:.c=.o)

all: $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@make -sC $(MLX_DIR)

%.o: %.c
	@echo "[$(GREEN)DONE$(RESET)] Compiling [$(YELLOW)$<$(RESET)] - File being compiled..."
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< 

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "[$(GREEN)DONE$(RESET)] Linking complete: [$(MAGENTA)$(NAME)$(RESET)] - Complete!"

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "[$(RED)DELETED$(RESET)] Object files [$(RED)*.o$(RESET)] - Cleaned!"

fclean:
	@$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(NAME)
	@echo "[$(RED)DELETED$(RESET)] Cub3D file [$(RED)$(NAME)$(RESET)] - Cleaned!"

re: fclean all

.PHONY:	all clean fclean re libmlx

.SILENT: