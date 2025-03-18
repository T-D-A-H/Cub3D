/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/18 16:25:51 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_cub *cub)
{
	int	index;

	if (x >= WINDOW_W || y >= WINDOW_H || x < 0 || y < 0)
		return;
	index = y * cub->game->size_line + x * cub->game->bpp / 8;
	cub->game->data[index] = color & 0xFF;
	cub->game->data[index + 1] = (color >> 8) & 0xFF;
	cub->game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_cub *cub)
{
	for (int i = 0;  i < size; i++)
		put_pixel(x + i, y, color, cub);
	for (int i = 0;  i < size; i++)
		put_pixel(x, y + i, color, cub);
	for (int i = 0;  i < size; i++)
		put_pixel(x + size, y + i, color, cub);
	for (int i = 0;  i < size; i++)
		put_pixel(x + i, y + size, color, cub);
}

void	move_player(t_cub *cub)
{
	int speed;

	speed = 5;
	if (cub->player->key_up)
		cub->player->player_y -= speed;
	if (cub->player->key_down)
		cub->player->player_y += speed;
	if (cub->player->key_left)
		cub->player->player_x -= speed;
	if (cub->player->key_right)
		cub->player->player_x += speed;
}

int key_press(int keycode, t_cub *cub)
{
    if (keycode == W) {
        cub->player->key_up = true;
        printf("Key W pressed\n");
    }
    if (keycode == A) {
        cub->player->key_left = true;
        printf("Key A pressed\n");
    }
    if (keycode == D) {
        cub->player->key_right = true;
        printf("Key D pressed\n");
    }
    if (keycode == S) {
        cub->player->key_down = true;
        printf("Key S pressed\n");
    }
    return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == W)
		cub->player->key_up = false;
	if (keycode == A)
		cub->player->key_left = false;
	if (keycode == D)
		cub->player->key_right = false;
	if (keycode == S)
		cub->player->key_down = false;
	return (0);
}

void	init_player(t_cub *cubed)
{
    cubed->player->player_x = WINDOW_W / 2;
    cubed->player->player_y = WINDOW_H / 2;

	cubed->player->key_up = false;
	cubed->player->key_down = false;
	cubed->player->key_left = false;
	cubed->player->key_right = false;
    cubed->player->player_angle = 0;
}

void	clear_image(t_cub *cub)
{
	for (int y = 0; y < WINDOW_H; y++)
		for (int x = 0; x < WINDOW_W; x++)
			put_pixel(x, y, 0, cub);
}

void	init_game(t_cub *cubed)
{
    cubed->game->mlx = mlx_init();
    cubed->game->win = mlx_new_window(cubed->game->mlx, WINDOW_W, WINDOW_H, WINDOW_NAME);
	cubed->game->img = mlx_new_image(cubed->game->mlx, WINDOW_W, WINDOW_H);
	cubed->game->data = mlx_get_data_addr(cubed->game->img, &cubed->game->bpp, &cubed->game->size_line, &cubed->game->endian);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win, cubed->game->img, 0, 0);
}

int	draw_loop(t_cub *cub)
{
	move_player(cub);
	clear_image(cub);
	printf("Posición después del movimiento: %f, %f\n", cub->player->player_x, cub->player->player_y);
	draw_square(cub->player->player_x, cub->player->player_y, 5, 0x00FF00, cub);
	mlx_put_image_to_window(cub->game->mlx, cub->game->win, cub->game->img, 0, 0);
	return (0);
}

void init_window(t_cub *cubed)
{
	init_player(cubed);
	init_game(cubed);
	mlx_hook(cubed->game->win, 2, 1L<<0, key_press, cubed);
	mlx_hook(cubed->game->win, 3, 1L<<1, key_release, cubed);
	mlx_loop_hook(cubed->game->mlx, draw_loop, cubed);
    mlx_loop(cubed->game->mlx);
}
