/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:25:02 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/21 13:11:13 by ctommasi         ###   ########.fr       */
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

void	draw_line(t_cub *cubed, int start_x, int start_y)
{
	int	i;
	int	j;
	int	k;
	int	new_x;
	int	new_y;

	i = 3;
	start_x += 16;
	start_y += 16;
	while (++i < 10)
	{
		new_x = start_x + cubed->player->dx * i;
		new_y = start_y + cubed->player->dy * i;
		j = -2;
		while (++j <= 4)
		{
			k = -2;
			while (++k <= 4)
			{
				put_pixel(new_x + k, new_y + j, GREEN, cubed);
			}
		}
	}
}


void	draw_loop(t_cub *cubed, t_player *player)
{
	// which box of the map were in
	int	mapX = (int)(BLOCK / player->x);
	int	mapY = (int)(BLOCK / player->y);

	// length of ray from current position
	double	sideDistX;
	double	sideDistY;

	// length of ray from one X or Y side next to X or Y side
	double	deltaDistX = fabs(BLOCK / player->dx);
	double	deltaDistY = fabs(BLOCK / player->dy);

	// what direction to step in
	int	stepX;
	int	stepY;

	if (player->dx < 0)
	{
		stepX = -1;
		sideDistX = ((player->x * BLOCK) - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - (player->x / BLOCK)) * deltaDistX;
	}
	if (player->dy < 0)
	{
		stepY = -1;
		sideDistY = ((player->y * BLOCK) - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - (player->y / BLOCK)) * deltaDistY;
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
		if (cubed->map[mapY][mapX] == '1')
			hit = 1;
	}

	// distance from player to wall hit
	double perpWallDist;

	if (side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);
	
	// height of line
	int	lineHeight = (int)(HEIGHT / perpWallDist);

	int	drawStart = -lineHeight / 2 + HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	
	int	drawEnd = lineHeight / 2 + HEIGHT / 2;
	if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	
	draw_line(cubed, player->x, player->y);
	draw_line(cubed, drawStart, drawEnd);
}