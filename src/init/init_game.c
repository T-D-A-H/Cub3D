/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/28 15:16:02 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_loop(t_loop *loop)
{
	loop->fov = PI / 3 / WIDTH;
	loop->ray_angle = 0;
	loop->raydir_x = 0;
	loop->raydir_y = 0;
	loop->sidedist_x = 0;
	loop->sidedist_y = 0;
	loop->map_x = 0;
	loop->map_y = 0;
	loop->deltadist_x = 0;
	loop->deltadist_y = 0;
	loop->step_x = 0;
	loop->step_y = 0;
	loop->hit = 0;
	loop->side = 0;
	loop->perpwalldist = 0;
	loop->line_height = 0;
	loop->drawstart = 0;
	loop->drawend = 0;
}

void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed)
{
	player->x = (double)((s_x * BLOCK));
	player->y = (double)((s_y * BLOCK));
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
/* 	draw_map(cubed);
	draw_empty_square((int)cubed->player->x / 4, (int)cubed->player->y / 4,
		8, cubed); */
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
	mlx_loop_hook(cubed->game->mlx, game_loop, cubed);
	mlx_loop(cubed->game->mlx);
}
