/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:03:36 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/07 15:15:48 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, int colour, t_cub *cubed)
{
	int	index;

	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return;
	index = y * cubed->game->size_line + x * cubed->game->bpp / 8;
	cubed->game->data[index] = colour & 0xFF;
	cubed->game->data[index + 1] = ((colour >> 8) & 0xFF);
	cubed->game->data[index + 2] = ((colour >> 16) & 0xFF);
}

void	clear_screen(t_cub *cubed)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 1, cubed);
	}
}

void	draw_3dmap(t_cub *cubed, int draw_start, int draw_end, int x)
{
	int	y;

	y = -1;
	while (++y <= draw_start)
	{
		if (y >= 0 && y < HEIGHT)
			put_pixel(x, y, cubed->c_color, cubed);
	}
	y = draw_end - 1;
	while (++y <= WIDTH)
	{
		put_pixel(x, y, cubed->f_color, cubed);
	}
}
