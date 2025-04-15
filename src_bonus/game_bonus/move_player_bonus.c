/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:05:38 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/15 11:47:52 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

void	strafe_player(t_player *player, double *next_x, double *next_y)
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

int	move_player(t_player *player, t_cub *cubed)
{
	double	next_x;
	double	next_y;

	next_x = player->x ;
	next_y = player->y ;
	strafe_player(player, &next_x, &next_y);
	if (can_move(cubed, next_x, player->y))
		player->x = next_x;
	if (can_move(cubed, player->x, next_y))
		player->y = next_y;
	rotate_player(player);
	player->mx = (int)(player->x / BLOCK);
	player->my = (int)(player->y / BLOCK);
	return (0);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	double	sensitivity;
	int		delta_x;
	int		center_x;

	(void)y;
	sensitivity = 0.00009;
	center_x = WIDTH / 2;
	if (!cub || !cub->player || !cub->game)
		return (0);
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	cub->player->angle += delta_x * sensitivity;
	cub->player->angle = fmod(cub->player->angle, 2 * PI);
	if (cub->player->angle < 0)
		cub->player->angle += 2 * PI;
	if (cub->player->angle > 2 * PI)
		cub->player->angle -= 2 * PI;
	cub->player->dx = cos(cub->player->angle) * 5;
	cub->player->dy = sin(cub->player->angle) * 5;
	mlx_mouse_move(cub->game->mlx, cub->game->win, center_x, HEIGHT / 2);
	return (0);
}
