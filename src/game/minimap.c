/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:04:20 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/01 10:55:18 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_mini(t_mini *mini, int x0, int y0, t_loop *loop)
{
	mini->dx = abs(loop->map_x * MAP - x0);
	mini->dy = abs(loop->map_y * MAP - y0);
	mini->sx = -1;
	mini->sy = -1;
	if (x0 < loop->map_x * MAP)
		mini->sx = 1;
	if (y0 < loop->map_y * MAP)
		mini->sy = 1;
	mini->err = mini->dx - mini->dy;
}
void	draw_rays(t_cub *cubed, int x0, int y0, t_loop *loop)
{
	t_mini	mini;

	init_mini(&mini, x0, y0, loop);
	while (x0 != loop->map_x * MAP || y0 != loop->map_y * MAP)
	{
		put_pixel(x0, y0, GREEN, cubed);
		mini.e2 = 2 * mini.err;
		if (mini.e2 > -mini.dy)
		{
			mini.err -= mini.dy;
			x0 += mini.sx;
		}
		if (mini.e2 < mini.dx)
		{
			mini.err += mini.dx;
			y0 += mini.sy;
		}
	}
}

void	draw_empty_square(int x, int y, int size, t_cub *cubed)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, YELLOW, cubed);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, YELLOW, cubed);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, YELLOW, cubed);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, YELLOW, cubed);
}

void	draw_full_square(t_cub *cubed, int x, int y, int colour)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MAP - 2)
	{
		j = -1;
		while (++j < MAP - 2)
			put_pixel(x * MAP + j, y * MAP + i, colour, cubed);
	}
}

void	draw_minimap(t_cub *cubed)
{
	int	y;
	int	x;

	draw_empty_square(((int)cubed->player->x / 4) - 4, ((int)cubed->player->y  / 4) - 4,
		8, cubed);
	y = -1;
	while (cubed->map[++y])
	{
		x = -1;
		while (cubed->map[y][++x])
		{
			if (cubed->map[y][x] == '1')
				draw_full_square(cubed, x, y, BLUE);
			else if (cubed->map[y][x] == '0' || cubed->map[y][x] == 'N'
				|| cubed->map[y][x] == 'E'
				|| cubed->map[y][x] == 'W'
				|| cubed->map[y][x] == 'S' )
				draw_full_square(cubed, x, y, GREY);
		}
	}
}
