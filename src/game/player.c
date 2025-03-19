/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:16:23 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/19 18:12:40 by ctommasi         ###   ########.fr       */
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
		player->p_x += player->p_d_x;
		player->p_y += player->p_d_y;
	}
	if (player->key_down)
	{
		player->p_x -= player->p_d_x;
		player->p_y -= player->p_d_y;
	}
	if (player->key_left)
	{
		player->p_angle -= 0.1;
		if (player->p_angle < 0)
			player->p_angle += 2 * PI;
		player->p_d_x = cos(player->p_angle) * 5;
		player->p_d_y = sin(player->p_angle) * 5;
		
	}
	if (player->key_right)
	{
		player->p_angle += 0.1;
		if (player->p_angle > 2 * PI)
			player->p_angle -= 2 * PI;
		player->p_d_x = cos(player->p_angle) * 5;
		player->p_d_y = sin(player->p_angle) * 5;
	}
	return (0);
}

int	update_player(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	clear_screen(cubed);
	draw_map(cubed);
	draw_empty_square(cubed->player->p_x, cubed->player->p_y, PLAYER_SIZE, 0xFFFF00, cubed);
	draw_line(cubed, cubed->player->p_x, cubed->player->p_y);
	move_player(cubed->player);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win, cubed->game->img, 0, 0);
	return (0);
}