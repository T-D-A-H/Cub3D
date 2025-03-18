/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:16:23 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/18 18:42:31 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int on_keypress(int keydata, t_player *player)
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

int on_keyrelease(int keydata, t_player *player)
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

int	move_player(t_player *player)
{
	if (player->key_up)
	{
		player->p_y -= MOVE_AMOUNT;
	}
	if (player->key_down)
	{
		player->p_y += MOVE_AMOUNT;
	}
	if (player->key_left)
	{
		player->p_x -= MOVE_AMOUNT;
	}
	if (player->key_right)
	{
		player->p_x += MOVE_AMOUNT;
	}
	return (0);
}

void	draw_player(float x, float y, int colour, t_game *game)
{
	int	i;

	i = -1;
	while (++i < 10)
	{
		mlx_pixel_put(game->mlx, game->win, x + i, y, colour);
		mlx_pixel_put(game->mlx, game->win, x, y + i, colour);
	}
}

int	update_player(t_cub *cubed)
{
	t_player	*player;
	t_game		*game;

	player = cubed->player;
	game = cubed->game;
	// move_player(player);
	draw_player(player->p_x, player->p_y, 1, game);
	return (0);
}