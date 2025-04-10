/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/10 12:22:13 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/cub3d.h"

void	init_struct(t_cub *cubed)
{
	cubed->no_path = NULL;
	cubed->so_path = NULL;
	cubed->we_path = NULL;
	cubed->ea_path = NULL;
	cubed->pj_x = -1;
	cubed->pj_y = -1;
	cubed->map = NULL;
	cubed->premap = NULL;
}

void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed)
{
	player->x = (double)((s_x * BLOCK)) + 32;
	player->y = (double)((s_y * BLOCK)) + 32;
	player->mx = (int)(player->x / BLOCK);
	player->my = (int)(player->y / BLOCK);
	player->angle = cubed->start_direction;
	player->dx = cos(player->angle) * 5;
	player->dy = sin(player->angle) * 5;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
	player->is_moving = false;
}

int get_pixel_color(int x, int y, t_cub *cubed)
{
	char *dst;
	int bytes_per_pixel;
	
	if (!cubed || !cubed->game || !cubed->game->data)
		return 0;
	
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return 0;
	
	bytes_per_pixel = cubed->game->bpp / 8;
	if (bytes_per_pixel <= 0)
		return 0;
	
	dst = cubed->game->data + (y * cubed->game->size_line + x * bytes_per_pixel);
	return (*(unsigned int*)dst);
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


int	game_loop(void *param)
{
	t_cub	*cubed;

	cubed = (t_cub *)param;
	if (BONUS)
	{
		cubed->blink_counter++;
		if (cubed->blink_counter > 10)
		{
			cubed->blink_counter = 0;
			cubed->blink_state = !cubed->blink_state;
		}	
	}
	clear_screen(cubed);
	move_player(cubed->player, cubed);
	raycasting(cubed, cubed->player, cubed->loop);
	if (BONUS)
	{
		cubed->animation_counter++;
		if (cubed->blink_state == 1)
			draw_red_dot(cubed);
		apply_vhs_effect(cubed);
		// draw_minimap(cubed);
	}
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win,
		cubed->game->img, 0, 0);
	return (0);
}

void	init_game(t_game *game, t_cub *cubed)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, W_NAME);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	load_all_textures(cubed);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	cubed->game->sees_door = 0;
}
void init_objects(t_cub *cubed)
{
	cubed->p_capacity = 50;
	cubed->p_positions = malloc(sizeof(t_position) * cubed->p_capacity);
	cubed->p_count = 0;
}

int mouse_move(int x, int y,  t_cub *cub)
{
	double sensitivity = 0.0002;
	int delta_x;
	int center_x = WIDTH / 2;
	
	(void)y;
	if (!cub || !cub->player || !cub->game)
		return (0);
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	cub->player->angle += delta_x * sensitivity;
	cub->player->angle = fmod(cub->player->angle, 2 * PI);
	if (cub->player->angle < 0)
		cub->player->angle += 2 * PI;
	if (cub->player->angle > 2 * PI)
		cub->player->angle -= 2 * PI;

	cub->player->dx = cos(cub->player->angle) * 5;
	cub->player->dy = sin(cub->player->angle) * 5;
	mlx_mouse_move(cub->game->mlx, cub->game->win, center_x, HEIGHT / 2);
	return (0);
}

void	init_window(t_cub *cubed)
{
	cubed->animation_counter = 0;
	if (BONUS)
		init_objects(cubed);
	if (BONUS)
		init_objects(cubed);
	init_player(cubed->player, cubed->pj_x, cubed->pj_y, cubed);
	init_sounds(cubed);
	init_game(cubed->game, cubed);
	mlx_hook(cubed->game->win, 2, 1L << 0, on_keypress, cubed);
	mlx_hook(cubed->game->win, 3, 1L << 1, on_keyrelease, cubed->player);
	if (BONUS)
	{
		mlx_mouse_hide(cubed->game->mlx, cubed->game->win);
		mlx_mouse_move(cubed->game->mlx, cubed->game->win, WIDTH / 2, HEIGHT / 2);
		mlx_hook(cubed->game->win, 6, 1L<<6, mouse_move, cubed);
	}
	if (BONUS)
	{
		mlx_mouse_hide(cubed->game->mlx, cubed->game->win);
		mlx_mouse_move(cubed->game->mlx, cubed->game->win, WIDTH / 2, HEIGHT / 2);
		mlx_hook(cubed->game->win, 6, 1L<<6, mouse_move, cubed);
	}
	mlx_loop_hook(cubed->game->mlx, game_loop, cubed);
	mlx_loop(cubed->game->mlx);
	if (BONUS)
		mlx_mouse_show(cubed->game->mlx, cubed->game->win);
	if (BONUS)
		mlx_mouse_show(cubed->game->mlx, cubed->game->win);
}
