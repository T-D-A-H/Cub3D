/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:03:36 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/11 17:36:40 by ctommasi         ###   ########.fr       */
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

int	get_pixel_color(int x, int y, t_cub *cubed)
{
	char	*dst;
	int		bpp;

	if (!cubed || !cubed->game || !cubed->game->data)
		return (0);
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	bpp = cubed->game->bpp / 8;
	if (bpp <= 0)
		return (0);
	dst = cubed->game->data + (y * cubed->game->size_line + x * bpp);
	return (*(unsigned int *)dst);
}

void apply_vhs_effect(t_cub *cubed)
{
	static int scan_line = 0;
	static int frame_counter = 0;
	int y, x, color;

	if (!cubed || !cubed->game)
		return;
	frame_counter++;
	scan_line = (scan_line + 1) % HEIGHT;
	if (frame_counter % 2 != 0)
		return;
	for (y = 0; y < HEIGHT; y++)
	{
		if (rand() % 5 == 0)
		{
			int noise = rand() % 50 - 25;
			for (x = 0; x < WIDTH; x += (rand() % 3 + 1))
			{
				color = get_pixel_color(x, y, cubed);
				int r = (color >> 16) & 0xFF;
				int g = (color >> 8) & 0xFF;
				int b = color & 0xFF;
				r = (r + noise) % 256;
				g = (g + noise) % 256;
				b = (b + noise + 15) % 256;
				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;
				put_pixel(x, y, (r << 16) | (g << 8) | b, cubed);
			}
		}
		if (y >= scan_line && y < scan_line + 5)
		{
			for (x = 0; x < WIDTH; x++)
			{
				color = get_pixel_color(x, y, cubed);
				int b = (color & 0xFF) + 40;
				b = b > 255 ? 255 : b;
				put_pixel(x, y, (color & 0xFFFF00) | b, cubed);
			}
		}
	}
}
