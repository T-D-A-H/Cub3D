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
	while (++i < BLOCK_SIZE - 1)
	{
		j = -1;
		while (++j < BLOCK_SIZE - 1)
			put_pixel(x * BLOCK_SIZE + j, y * BLOCK_SIZE + i, colour, cubed);
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
				draw_empty_square(x * BLOCK_SIZE, y * BLOCK_SIZE,
					BLOCK_SIZE, BLUE, cubed);
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
		new_x = start_x + cubed->player->p_d_x * i;
		new_y = start_y + cubed->player->p_d_y * i;
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

void draw_linex(t_cub *cubed, int s_x, int s_y, int e_x, int e_y)
{
	for (int k = 0; k < 4; k++)
		for (int i = s_y - PLAYER_SIZE; i < s_y; i++)
			for (int j = s_x + PLAYER_SIZE; j < s_x * 2; j++)
				put_pixel(j + k, i + k, GREEN, cubed);
			
}

void	drawRays3D(t_cub *cubed)
{
	// CONVERT PIXEL POS TO GRID POS
	int	map_x = (int)(cubed->player->p_x / BLOCK_SIZE);
	int	map_y = (int)(cubed->player->p_y / BLOCK_SIZE);

	float side_distance_x;
	float side_distance_y;
	
	// FIND THE FIRST GRID INTERSECTION
	float	delta_dx = fabs(BLOCK_SIZE / cubed->player->p_d_x);
	float	delta_dy = fabs(BLOCK_SIZE / cubed->player->p_d_y);

	int step_x;
	int step_y;

	if (cubed->player->p_d_x < 0)
	{
		step_x = -1;
		side_distance_x = (cubed->player->p_x - (map_x * BLOCK_SIZE)) * delta_dx;
	}
	else
	{
		step_x = 1;
		side_distance_x = ((map_x + 1) - (cubed->player->p_x / BLOCK_SIZE)) * delta_dx;
	}
	if (cubed->player->p_d_y < 0)
	{
		step_y = -1;
		side_distance_y = (cubed->player->p_y - (map_y * BLOCK_SIZE)) * delta_dy;
	}
	else
	{
		step_y = 1;
		side_distance_y = ((map_y + 1) - (cubed->player->p_y / BLOCK_SIZE)) * delta_dy;
	}

	int hit = 0;
	int side;

	while (!hit)
	{
		if (side_distance_x < side_distance_y)
		{
			side_distance_x += delta_dx;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_distance_y += delta_dy;
			map_y += step_y;
			side = 1;
		}
		if (cubed->map[map_y][map_x] == '1')
			hit = 1;
	}
	float hit_x = cubed->player->p_x;
	float hit_y = cubed->player->p_y;
	
	if (side == 0)
		hit_x += (side_distance_x - delta_dx) * cubed->player->p_d_x;
	else
		hit_y += (side_distance_y - delta_dx) * cubed->player->p_d_y;
	
	
	draw_linex(cubed, cubed->player->p_x, cubed->player->p_y, hit_x, hit_y);

}