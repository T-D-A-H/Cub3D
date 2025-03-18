# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 13:05:04 by jaimesan          #+#    #+#              #
#    Updated: 2025/03/18 12:13:43 by ctommasi         ###   ########.fr        #
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

MLX_DIR = ./MLX42/build
MLX = $(MLX_DIR)/libmlx42.a -ldl -lglfw -pthread -lm

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m
YELLOW := \033[33m
CYAN := \033[36m
MAGENTA := \033[35m
BLUE := \033[34m

# Archivos fuente
SRCS =	./src/main/main.c ./src/utils/check_args.c ./src/utils/init_struct.c ./src/utils/init_variables.c \
		./src/main/error.c ./src/utils/init_map.c ./src/utils/delete_after.c ./src/utils/ft_check_lines.c \
		./src/utils/save_map.c \
		./src/utils/init_window.c
# Archivos objeto
OBJS = $(SRCS:.c=.o)


all: libmlx $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@echo "[$(GREEN)DONE$(RESET)] Compiling [$(YELLOW)$<$(RESET)] - File being compiled..."
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< 

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "[$(GREEN)DONE$(RESET)] Linking complete: [$(MAGENTA)$(NAME)$(RESET)] - Complete!"

libmlx:
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) $(OBJS)
	@echo "[$(RED)DELETED$(RESET)] Object files [$(RED)*.o$(RESET)] - Cleaned!"

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) $(OBJS) $(NAME)
	@echo "[$(RED)DELETED$(RESET)] Cub3D file [$(RED)$(NAME)$(RESET)] - Cleaned!"

re: fclean all

.PHONY:	all clean fclean re libmlx

.SILENT: