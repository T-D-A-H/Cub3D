/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:57:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/28 13:09:00 by jaimesan         ###   ########.fr       */
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
	if (keydata == ESC)
		exit(0);
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
