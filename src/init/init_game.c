/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/26 12:52:34 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	game_loop(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	clear_screen(cubed);
	// draw_map(cubed);
	// draw_empty_square(cubed->player->x, cubed->player->y,
	// 	PLAYER_SIZE, YELLOW, cubed);
	move_player(cubed->player);
	raycasting(cubed, cubed->player, cubed->loop);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win,
		cubed->game->img, 0, 0);
	return (0);
}

void	init_loop(t_loop *loop)
{
	loop->fov = PI / 3 / WIDTH;
	loop->ray_angle = 0;
	loop->rayDirX = 0;
	loop->rayDirY = 0;
	loop->sideDistX = 0;
	loop->sideDistY = 0;
	loop->mapX = 0;
	loop->mapY = 0;
	loop->deltaDistX = 0;
	loop->deltaDistY = 0;
	loop->stepX = 0;
	loop->stepY = 0;
	loop->hit = 0;
	loop->side = 0;
	loop->perpWallDist = 0;
	loop->lineHeight = 0;
	loop->drawStart = 0;
	loop->drawEnd = 0;
}

void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed)
{
	player->x = (double)((s_x * WIDTH) / ft_strlen(cubed->map[0]));
	player->y = (double)((s_y * HEIGHT) / ft_arrlen(cubed->map));
	player->mx = (int)(player->x / BLOCK);
	player->my = (int)(player->y / BLOCK);
	player->angle = cubed->start_direction;
	player->dx = cos(player->angle) * 5;
	player->dy = sin(player->angle) * 5;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, W_NAME);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	init_window(t_cub *cubed)
{
	init_player(cubed->player, cubed->pj_x, cubed->pj_y, cubed);
	init_game(cubed->game);
	mlx_hook(cubed->game->win, 2, 1L << 0, on_keypress, cubed->player);
	mlx_hook(cubed->game->win, 3, 1L << 1, on_keyrelease, cubed->player);
	mlx_loop_hook(cubed->game->mlx, game_loop, cubed);
	mlx_loop(cubed->game->mlx);
}
