/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:04:20 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/27 16:19:20 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void draw_rays(t_cub *cubed, int x0, int y0, int x1, int y1, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = -1;
	sy = -1;
	err = dx - dy;
	if (x0 < x1)
		sx = 1;
	if (y0 < y1)
		sy = 1;
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
