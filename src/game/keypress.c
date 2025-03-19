/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:16:23 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/19 15:23:22 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int on_keypress(int keydata, t_player *player)
{
	if (keydata == W)
		player->key_up = true;
	if (keydata == S)
		player->key_down = true;
	if (keydata == A)
		player->key_left = true;
	if (keydata == D)
		player->key_right = true;
	return (0);
}

int on_keyrelease(int keydata, t_player *player)
{
	if (keydata == W)
		player->key_up = false;
	if (keydata == S)
		player->key_down = false;
	if (keydata == A)
		player->key_left = false;
	if (keydata == D)
		player->key_right = false;
	return (0);
}

static int	move_player(t_player *player)
{
	if (player->key_up)
	{
		player->p_y -= MOVE_AMOUNT;
	}
	if (player->key_down)
	{
		player->p_y += MOVE_AMOUNT;
	}
	if (player->key_left)
	{
		player->p_x -= MOVE_AMOUNT;
	}
	if (player->key_right)
	{
		player->p_x += MOVE_AMOUNT;
	}
	return (0);
}

static void	put_pixel(int x, int y, int colour, t_cub *cubed)
{
	int	index;
	
	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;
	index = y * cubed->game->size_line + x * cubed->game->bpp / 8;
	cubed->game->data[index] = colour & 0xFF;
	cubed->game->data[index + 1] = ((colour >> 8) & 0xFF);
	cubed->game->data[index + 2] = ((colour >> 16) & 0xFF);
}

static void draw_square(int x, int y, int size, int color, t_cub *cubed)
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

static void draw_map(int colour, t_cub *cubed)
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
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, colour, cubed);
		}
	}
}

static void clear_screen(t_cub *cubed)
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

int	update_player(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	clear_screen(cubed);
	draw_map(0x0000FF, cubed);
	draw_square(cubed->player->p_x, cubed->player->p_y, 25, 0x00FF00, cubed);
	move_player(cubed->player);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win, cubed->game->img, 0, 0);
	return (0);
}