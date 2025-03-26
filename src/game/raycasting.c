/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/26 12:53:48 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_raycast_steps(t_player *player, t_loop *loop)
{
	if (loop->rayDirX < 0)
	{
		loop->stepX = -1;
		loop->sideDistX = ((player->x / BLOCK) - loop->mapX) * loop->deltaDistX;
	}
	else
	{
		loop->stepX = 1;
		loop->sideDistX = ((loop->mapX + 1.0) - (player->x / BLOCK)) * loop->deltaDistX;
	}
	if (loop->rayDirY < 0)
	{
		loop->stepY = -1;
		loop->sideDistY = ((player->y / BLOCK) - loop->mapY) * loop->deltaDistY;
	}
	else
	{
		loop->stepY = 1;
		loop->sideDistY = ((loop->mapY + 1.0) - (player->y / BLOCK)) * loop->deltaDistY;
	}
}

void	get_raycast_hits(t_cub *cubed, t_loop *loop)
{
	loop->hit = 0;
	while (loop->hit == 0)
	{
		if (loop->sideDistX < loop->sideDistY)
		{
			loop->sideDistX += loop->deltaDistX;
			loop->mapX += loop->stepX;
			loop->side = 0;
		}
		else
		{
			loop->sideDistY += loop->deltaDistY;
			loop->mapY += loop->stepY;
			loop->side = 1;

		}
		if (loop->mapY < 0 || loop->mapX < 0
			|| loop->mapY >= HEIGHT / BLOCK || loop->mapX >= WIDTH / BLOCK)
    		break ;
		if (cubed->map[loop->mapY][loop->mapX] == '1')
			loop->hit = 1;
	}
}

void	raycasting(t_cub *cubed, t_player *player, t_loop *loop)
{
	int	x;

	x = -1;
	init_loop(loop);
	while (++x < WIDTH)
	{
		loop->ray_angle = player->angle - (PI / 6) + (x * loop->fov);
		loop->rayDirX = cos(loop->ray_angle);
		loop->rayDirY = sin(loop->ray_angle);
		loop->deltaDistX = fabs(1 / loop->rayDirX);
		loop->deltaDistY = fabs(1 / loop->rayDirY);
		loop->mapX = player->mx;
		loop->mapY = player->my;
		get_raycast_steps(player, cubed->loop);
		get_raycast_hits(cubed, loop);
		if (loop->side == 0)
			loop->perpWallDist = (loop->sideDistX - loop->deltaDistX);
		else
			loop->perpWallDist = (loop->sideDistY - loop->deltaDistY);
		loop->lineHeight = (int)(HEIGHT / loop->perpWallDist);
		loop->drawStart = -loop->lineHeight / 2 + HEIGHT / 2;
		if (loop->drawStart < 0)
			loop->drawStart = 0;
		loop->drawEnd = loop->lineHeight / 2 + HEIGHT / 2;
		if (loop->drawEnd >= HEIGHT)
			loop->drawEnd = HEIGHT - 1;
		draw_3dmap(cubed, loop->drawStart,  loop->drawEnd, x,  loop->side);
	}
}

