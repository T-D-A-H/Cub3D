/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/25 17:47:38 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void clear_screen(t_cub *cubed)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, cubed);
	}
}
void	draw_loop(t_cub *cubed, t_player *player)
{
	t_loop *loop;

	loop = cubed->loop;
	loop->fov = PI / 3 / WIDTH;
	for (int x = 0; x < WIDTH; x++)
	{
		// Compute the current ray angle
		loop->ray_angle = player->angle - (PI / 6) + (x * loop->fov);
		loop->rayDirX = cos(loop->ray_angle);
		loop->rayDirY = sin(loop->ray_angle);

		// length of ray from current position
		loop->mapX = player->mx;
		loop->mapY = player->my;
		
		// length of ray from one X or Y side next to X or Y side
		loop->deltaDistX = fabs(1 / loop->rayDirX);
		loop->deltaDistY = fabs(1 / loop->rayDirY);
	
		// hit
		loop->hit = 0;
		
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
		
		// Draw a line from player to the hit point
		draw_rays(cubed, player->x + 16, player->y + 16, loop->mapX * BLOCK, loop->mapY * BLOCK, GREEN);
		//draw_3dmap(cubed, loop->drawStart,  loop->drawEnd, x,  loop->side);
		}
}

int	game_loop(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	clear_screen(cubed);
	// draw_map(cubed);
	// draw_empty_square(cubed->player->x, cubed->player->y,
	// 	PLAYER_SIZE, YELLOW, cubed);
	move_player(cubed->player);
	draw_loop(cubed, cubed->player);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win,
		cubed->game->img, 0, 0);
	return (0);
}