/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:04:20 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/11 17:21:59 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

	y = -1;
	while (cubed->map[++y])
	{
		x = -1;
		while (cubed->map[y][++x])
		{
			if (cubed->map[y][x] == '1')
				draw_full_square(cubed, x, y, BLUE);
			if (cubed->map[y][x] == 'D')
				draw_full_square(cubed, x, y, RED);
			if (cubed->map[y][x] == 'd')
				draw_full_square(cubed, x, y, GREEN);
			else if (cubed->map[y][x] == '0' || cubed->map[y][x] == 'N'
				|| cubed->map[y][x] == 'E'
				|| cubed->map[y][x] == 'W'
				|| cubed->map[y][x] == 'K'
				|| cubed->map[y][x] == 'S' )
				draw_full_square(cubed, x, y, GREY);
		}
	}
	draw_empty_square(((int)cubed->player->x / 4) - 4,
		((int)cubed->player->y / 4) - 4, 8, cubed);
}
