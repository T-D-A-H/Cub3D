/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/20 11:52:21 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void init_player(t_player *player, int s_x, int s_y, t_cub *cubed)
{
	player->p_x = (float)((s_x * WIDTH) / ft_strlen(cubed->map[0]));
	player->p_y = (float)((s_y * HEIGHT) / ft_arrlen(cubed->map));
	player->p_angle = cubed->start_direction;
	player->p_d_x = cos(player->p_angle) * 5;
	player->p_d_y = sin(player->p_angle) * 5;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}

static void	init_game(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, W_NAME);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void init_window(t_cub *cubed)
{
	init_player(cubed->player, cubed->pj_x, cubed->pj_y, cubed);
	init_game(cubed->game);
	mlx_hook(cubed->game->win, 2, 1L<<0, on_keypress, cubed->player);
	mlx_hook(cubed->game->win, 3, 1L<<1, on_keyrelease,  cubed->player);
	mlx_loop_hook(cubed->game->mlx, update_player, cubed);
    mlx_loop(cubed->game->mlx);
}
