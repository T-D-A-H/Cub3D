/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:25:02 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/25 13:37:41 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, int colour, t_cub *cubed)
{
	int	index;

	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;
	index = y * cubed->game->size_line + x * cubed->game->bpp / 8;
	cubed->game->data[index] = colour & 0xFF;
	cubed->game->data[index + 1] = ((colour >> 8) & 0xFF);
	cubed->game->data[index + 2] = ((colour >> 16) & 0xFF);
}

void	draw_empty_square(int x, int y, int size, int color, t_cub *cubed)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, color, cubed);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, color, cubed);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, color, cubed);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, color, cubed);
}

void	draw_full_square(t_cub *cubed, int x, int y, int colour)
{
	int	i;
	int	j;

	i = -1;
	while (++i < BLOCK - 2)
	{
		j = -1;
		while (++j < BLOCK - 2)
			put_pixel(x * BLOCK + j, y * BLOCK + i, colour, cubed);
	}
}

void	draw_map(t_cub *cubed)
{
	int	y;
	int	x;

	y = -1;
	while (cubed->map[++y])
	{
		x = -1;
		while (cubed->map[y][++x])
		{
			if (cubed->map[y][x] == '1')
				draw_full_square(cubed, x, y, PURPLE);
			else if (cubed->map[y][x] == '0')
				draw_empty_square(x * BLOCK, y * BLOCK, BLOCK, BLUE, cubed);
		}
	}
}

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


void draw_rays(t_cub *cubed, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (x0 != x1 || y0 != y1)
	{
		put_pixel(x0, y0, color, cubed);
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_3dmap(t_cub *cubed, int drawStart, int drawEnd, int x, int side)
{
	int color = PURPLE;
	for (int y = drawStart; y <= drawEnd; y++)
  	{
		if (side == 1)
			color = 0x690067  ;
  	    if (y >= 0 && y < HEIGHT)
  	        put_pixel(x, y, color, cubed);
  	}
}

void	draw_loop(t_cub *cubed, t_player *player)
{
	double fraction = PI / 3 / WIDTH;
	for (int x = 0; x < WIDTH; x++)
	{
		// Compute the current ray angle
		double ray_angle = player->angle - (PI / 6) + (x * fraction);
		double rayDirX = cos(ray_angle);
		double rayDirY = sin(ray_angle);
		// length of ray from current position
		double	sideDistX;
		double	sideDistY;
		int	mapX = player->mx;
		int	mapY = player->my;
		
		// length of ray from one X or Y side next to X or Y side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
	
		int	stepX;
		int	stepY;
	
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = ((player->x / BLOCK) - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = ((mapX + 1.0) - (player->x / BLOCK)) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = ((player->y / BLOCK) - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = ((mapY + 1.0) - (player->y / BLOCK)) * deltaDistY;
		}
		
		// did we hit a wall?
		int hit = 0;
		
		// was it a NS or EW wall hit?
		int side;
	
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;

			}
			if (mapY < 0 || mapX < 0 || mapY >= HEIGHT / BLOCK || mapX >= WIDTH / BLOCK)
    			break ;
			if (cubed->map[mapY][mapX] == '1')
				hit = 1;
			// else if (cubed->map[mapY - 1][mapX - 1] == '1')
			// 	hit = 1;
			// else if (cubed->map[mapY][mapX - 1] == '1')
			// 	hit = 1;
			// else if (cubed->map[mapY - 1][mapX] == '1')
			// 	hit = 1;

		}
		double perpWallDist;
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		int	lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		
		// Draw a line from player to the hit point
		draw_rays(cubed, player->x + 16, player->y + 16, mapX * BLOCK, mapY * BLOCK, GREEN);
		//draw_3dmap(cubed, drawStart, drawEnd, x, side);
		}
}
