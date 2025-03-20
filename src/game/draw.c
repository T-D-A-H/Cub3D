/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:25:02 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/20 18:24:16 by ctommasi         ###   ########.fr       */
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

static bool wall_not_reached(float px, float py, t_cub *cubed)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (cubed->map[y][x] == '1')
		return (true);
	return (false);
}

static void cast_rays(t_cub *cubed, t_player *player, float start_x)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	ray_x = player->x + 16;
	ray_y = player->y + 16;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!wall_not_reached(ray_x, ray_y, cubed))
	{
		put_pixel(ray_x, ray_y, GREEN, cubed);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

void	draw_loop(t_cub *cubed, t_player *player)
{
	float	fraction;
	float	start_x;
	int		i;

	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		cast_rays(cubed, player, start_x);
		start_x += fraction;
		i++;
	}
}