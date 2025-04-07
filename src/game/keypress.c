/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:57:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/07 15:29:16 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_keypress(int keydata, t_cub *cub)
{
	if (keydata == W)
		cub->player->key_w = true;
	if (keydata == S)
		cub->player->key_s = true;
	if (keydata == A)
		cub->player->key_a = true;
	if (keydata == D)
		cub->player->key_d = true;
	if (keydata == LEFT)
		cub->player->key_left = true;
	if (keydata == RIGHT)
		cub->player->key_right = true;
	if (keydata == KEY_F)
	{
		cub->player->key_f = true;
		if (door_is_closed(cub, cub->player) && cub->p_positions->is_taken == 1)
			open_door(cub, cub->player);
	}
	if (keydata == ESC)
		return (error(cub, NO_ERROR), 1);
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
	if (keydata == KEY_F)
		player->key_f = false;
	return (0);
}
