/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:25:02 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/21 17:23:08 by ctommasi         ###   ########.fr       */
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
				draw_empty_square(x * BLOCK, y * BLOCK,
					BLOCK, BLUE, cubed);
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


void draw_line(t_cub *cubed, int x0, int y0, int x1, int y1, int color)
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

void	draw_loop(t_cub *cubed, t_player *player)
{
	// length of ray from current position
	double	sideDistX;
	double	sideDistY;

	// length of ray from one X or Y side next to X or Y side
	double deltaDistX = fabs(1 / player->dx);
	double deltaDistY = fabs(1 / player->dy);


	int	stepX;
	int	stepY;

	if (player->dx < 0)
	{
		stepX = -1;
		sideDistX = ((player->x / BLOCK) - player->mx) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (player->mx + 1.0 - (player->x / BLOCK)) * deltaDistX;
	}
	if (player->dy < 0)
	{
		stepY = -1;
		sideDistY = ((player->y / BLOCK) - player->my) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (player->my + 1.0 - (player->y / BLOCK)) * deltaDistY;
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
			player->mx += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			player->my += stepY;
			side = 1;
		}

		if (stepY == -1 && cubed->map[player->my - 1][player->mx] == '1') 
			hit = 1;
		else if (stepX == -1 && cubed->map[player->my][player->mx - 1] == '1') 
			hit = 1;
		else if (stepY == 1 && cubed->map[player->my][player->mx] == '1') 
			hit = 1;
		else if (stepX == 1 && cubed->map[player->my][player->mx] == '1') 
			hit = 1;
	}

	// Draw a line from player to the hit point
	draw_line(cubed, player->x + 16, player->y + 16, player->mx * BLOCK, player->my * BLOCK, GREEN);
}
