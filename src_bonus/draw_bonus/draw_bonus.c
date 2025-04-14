/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:03:36 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/14 15:09:52 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

void	draw_red_dot(t_cub *cubed)
{
	int	center_x;
	int	center_y;
	int	y;
	int	x;

	center_x = WIDTH - DOT_MARGIN - DOT_RADIUS;
	center_y = DOT_MARGIN + DOT_RADIUS;
	y = -DOT_RADIUS;
	while (y <= DOT_RADIUS)
	{
		x = -DOT_RADIUS;
		while (x <= DOT_RADIUS)
		{
			if (x * x + y * y <= DOT_RADIUS * DOT_RADIUS)
				put_pixel(center_x + x, center_y + y, 0xFF0000, cubed);
			x += 1;
		}
		y += 2;
	}
}

void	draw_text(t_cub *cub, int texture_index)
{
	int		start_x;
	int		start_y;
	int		x;
	int		y;
	int		color;

	start_x = (WIDTH - cub->textures[texture_index]->width) / 2;
	start_y = (HEIGHT - cub->textures[texture_index]->height) / 2 + 300;
	y = 0;
	while (y < cub->textures[texture_index]->height)
	{
		x = 0;
		while (x < cub->textures[texture_index]->width)
		{
			color = cub->textures[texture_index]->data[
				y * cub->textures[texture_index]->width + x];
			put_pixel(start_x + x, start_y + y, color, cub);
			x++;
		}
		y++;
	}
}
