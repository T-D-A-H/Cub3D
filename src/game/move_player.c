/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:05:38 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/10 12:19:21 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	can_move(t_cub *cubed, double next_x, double next_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(next_x / BLOCK);
	map_y = (int)(next_y / BLOCK);
	if (map_x < 0 || map_y < 0 || map_x >= (int)ft_strlen(cubed->map[0])
		|| map_y >= ft_arrlen(cubed->map))
		return (0);
	if (cubed->map[map_y][map_x] == '1'
		|| cubed->map[map_y][map_x] == 'D' || cubed->map[map_y][map_x] == 'x')
		return (0);
	return (1);
}

void	rotate_player(t_player *player)
{
	if (player->key_left)
	{
		player->angle -= 0.1;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (player->key_right)
	{
		player->angle += 0.1;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
}

void	key_player(t_player *player, double *next_x, double *next_y)
{
	if (player->key_w)
	{
		*next_x += cos(player->angle) * MOVE_AMOUNT;
		*next_y += sin(player->angle) * MOVE_AMOUNT;
	}
	if (player->key_s)
	{
		*next_x -= cos(player->angle) * MOVE_AMOUNT;
		*next_y -= sin(player->angle) * MOVE_AMOUNT;
	}
	if (player->key_a)
	{
		*next_x += sin(player->angle) * MOVE_AMOUNT;
		*next_y -= cos(player->angle) * MOVE_AMOUNT;
	}
	if (player->key_d)
	{
		*next_x -= sin(player->angle) * MOVE_AMOUNT;
		*next_y += cos(player->angle) * MOVE_AMOUNT;
	}
}

void	strafe_player(t_player *player, t_cub *cubed)
{
	double	next_x;
	double	next_y;

	next_x = player->x ;
	next_y = player->y ;
	key_player(player, &next_x, &next_y);
	if (can_move(cubed, next_x, player->y))
		player->x = next_x;
	if (can_move(cubed, player->x, next_y))
		player->y = next_y;
	(void)cubed;
}

int	move_player(t_player *player, t_cub *cub)
{

	rotate_player(player);
	strafe_player(player, cub);
	player->mx = (int)(player->x / BLOCK);
	player->my = (int)(player->y / BLOCK);
	return (0);
}

