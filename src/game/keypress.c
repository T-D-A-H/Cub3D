/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:57:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/10 15:01:50 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_keypress(int keydata, t_cub *cub)
{
	if (keydata == W_KEY)
		cub->player->key_w = true;
	if (keydata == S_KEY)
		cub->player->key_s = true;
	if (keydata == A_KEY)
		cub->player->key_a = true;
	if (keydata == D_KEY)
		cub->player->key_d = true;
	if (keydata == LEFT_KEY)
		cub->player->key_left = true;
	if (keydata == RIGHT_KEY)
		cub->player->key_right = true;
	if (keydata == ESC_KEY)
		return (error(cub, NO_ERROR, 1), 1);
	return (0);
}

int	on_keyrelease(int keydata, t_player *player)
{
	if (keydata == W_KEY)
		player->key_w = false;
	if (keydata == S_KEY)
		player->key_s = false;
	if (keydata == A_KEY)
		player->key_a = false;
	if (keydata == D_KEY)
		player->key_d = false;
	if (keydata == LEFT_KEY)
		player->key_left = false;
	if (keydata == RIGHT_KEY)
		player->key_right = false;
	return (0);
}
