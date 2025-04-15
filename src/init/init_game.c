/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:46:19 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/15 12:47:33 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_struct(t_cub *cubed)
{
	cubed->no_path = NULL;
	cubed->so_path = NULL;
	cubed->we_path = NULL;
	cubed->ea_path = NULL;
	cubed->pj_x = -1;
	cubed->pj_y = -1;
	cubed->map = NULL;
	cubed->premap = NULL;
}

void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed)
{
	player->x = (double)((s_x * BLOCK)) + 32;
	player->y = (double)((s_y * BLOCK)) + 32;
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

int	game_loop(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	clear_screen(cubed);
	move_player(cubed->player, cubed);
	raycasting(cubed, cubed->player, cubed->loop);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win,
		cubed->game->img, 0, 0);
	return (0);
}

void	init_game(t_game *game, t_cub *cubed)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, W_NAME);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	load_all_textures(cubed);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	init_window(t_cub *cubed)
{
	init_player(cubed->player, cubed->pj_x, cubed->pj_y, cubed);
	init_game(cubed->game, cubed);
	mlx_hook(cubed->game->win, 2, 1L << 0, on_keypress, cubed);
	mlx_hook(cubed->game->win, 3, 1L << 1, on_keyrelease, cubed->player);
	mlx_hook(cubed->game->win, 17, 0, close_window, cubed);
	mlx_loop_hook(cubed->game->mlx, game_loop, cubed);
	mlx_loop(cubed->game->mlx);
}
