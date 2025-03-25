/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:57:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/25 17:44:53 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_keypress(int keydata, t_player *player)
{
	if (keydata == W)
		player->key_w = true;
	if (keydata == S)
		player->key_s = true;
	if (keydata == A)
		player->key_a = true;
	if (keydata == D)
		player->key_d = true;
	if (keydata == LEFT)
		player->key_left = true;
	if (keydata == RIGHT)
		player->key_right = true;
	return (0);
}

int	on_keyrelease(int keydata, t_player *player)
{
	if (keydata == W)
		player->key_w = false;
	if (keydata == S)
		player->key_s = false;
	if (keydata == A)
		player->key_a = false;
	if (keydata == D)
		player->key_d = false;
	if (keydata == LEFT)
		player->key_left = false;
	if (keydata == RIGHT)
		player->key_right = false;
	return (0);
}

void	rotate_player(t_player *player)
{
	if (player->key_left)
	{
		player->angle -= 0.1;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (player->key_right)
	{
		player->angle += 0.1;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
}

void	strafe_player(t_player *player)
{
	if (player->key_w)
	{
		player->x += player->dx;
		player->y += player->dy;
		
	}
	if (player->key_s)
	{
		player->x -= player->dx;
		player->y -= player->dy;

	}
	if (player->key_a)
	{
		player->x += sin(player->angle) * 5;
		player->y -= cos(player->angle) * 5;
	}
	if (player->key_d)
	{
		player->x -= sin(player->angle) * 5;
		player->y += cos(player->angle) * 5;
	}
}


int	move_player(t_player *player)
{
	rotate_player(player);
	strafe_player(player);
	player->mx = (int)(player->x / BLOCK);
	player->my = (int)(player->y / BLOCK);
	return (0);
}