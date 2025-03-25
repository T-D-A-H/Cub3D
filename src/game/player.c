/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:16:23 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/25 13:22:40 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_keypress(int keydata, t_player *player)
{
	if (keydata == W)
		player->key_up = true;
	if (keydata == S)
		player->key_down = true;
	if (keydata == A)
		player->key_left = true;
	if (keydata == D)
		player->key_right = true;
	return (0);
}

int	on_keyrelease(int keydata, t_player *player)
{
	if (keydata == W)
		player->key_up = false;
	if (keydata == S)
		player->key_down = false;
	if (keydata == A)
		player->key_left = false;
	if (keydata == D)
		player->key_right = false;
	return (0);
}

int	move_player(t_player *player, t_cub *cubed)
{
	if (player->key_left)
	{
		player->angle -= 0.1;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
		player->mx = (int)(player->x / BLOCK);
		player->my = (int)(player->y / BLOCK);
	}
	if (player->key_right)
	{
		player->angle += 0.1;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
		player->mx = (int)(player->x / BLOCK);
		player->my = (int)(player->y / BLOCK);
	}
	if (player->key_up)
	{
		if (cubed->map[(int)(player->my + player->dy /  4.2)][player->mx] == '1'
			|| cubed->map[player->my][(int)(player->mx + player->dx / 4.2)] == '1')
			return (0);
		player->x += player->dx;
		player->y += player->dy;
		player->mx = (int)(player->x / BLOCK);
		player->my = (int)(player->y / BLOCK);
		
	}
	if (player->key_down)
	{
		if (cubed->map[(int)(player->my - player->dy / 4.2)][player->mx] == '1'
			|| cubed->map[player->my][(int)(player->mx - player->dx / 4.2)] == '1')
			return (0);
		player->x -= player->dx;
		player->y -= player->dy;
			player->mx = (int)(player->x / BLOCK);
			player->my = (int)(player->y / BLOCK);	
	}
	return (0);
}

int	game_loop(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	clear_screen(cubed);
	draw_map(cubed);
	draw_empty_square(cubed->player->x, cubed->player->y,
		PLAYER_SIZE, YELLOW, cubed);
	move_player(cubed->player, cubed);
	draw_loop(cubed, cubed->player);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win,
		cubed->game->img, 0, 0);
	return (0);
}
