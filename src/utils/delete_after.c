/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:01:38 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/18 17:14:30 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_where_not_walled(char **map, int y, int x)
{
	int		i;
	int		j;

	i = 6;
	while (map[i])
	{
		if (i != y)
			printf("\033[1;32m%s\033[0m\n", map[i]);
		else
		{
			j = 0;
			while (map[i][j])
			{
				if (j != x)
					printf("\033[1;32m%c\033[0m", map[i][j]);
				else
					printf("\033[1;31m%c\033[0m", map[i][j]);
				j++;
			}
			printf("\n");
		}
		i++;
	}
}
static void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->angle = PI / 2;
}

static int key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

static int key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

static void move_player(t_player *player)
{
	int speed = 3;
	float angle_speed = 0.03;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
		
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_right)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
}

static void	put_pixel(int x, int y, int color, t_data *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = ((color >> 8) & 0xFF);
	game->data[index + 2] = ((color >> 16) & 0xFF);
}

// static void draw_square(int x, int y, int size, int color, t_data *game)
// {
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + i, y, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x, y + i, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + size, y + i, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + i, y + size, color, game);
// }

static void	init_game(t_cub *cubed, t_data *game)
{
	init_player(&game->player);
	game->map = cubed->map;
	game->mlx_ptr = mlx_init();
	game->window = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, WINDOW_NAME);
	game->img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx_ptr, game->window, game->img, 0, 0);
}

static void clear_image(t_data *game)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			put_pixel(x, y, 0, game);
		}
	}
}

// static void draw_map(t_data *game)
// {
// 	char **map = game->map;
// 	int color = 0x0000FF;
// 	for (int y = 0; map[y]; y++)
// 		for (int x = 0; map[y][x]; x++)
// 			if (map[y][x] == '1')
// 				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
// }

static bool	touch(float px, float py, t_data *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if (game->map[y][x] == '1')
		return true;
	return false;
}

static float distance(float x, float y)
{
	return (sqrt((x * x) + (y * y)));
}

static float fixed_dist(float x1, float y1, float x2, float y2, t_data *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fixed_dist = distance(delta_x, delta_y) * cos(angle);
	return (fixed_dist);
}

static void draw_line(t_player *player, t_data *game, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, 0xFF00000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;

	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}

static int draw_loop(t_data *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	// draw_square(player->x, player->y, 10, 0x00FF00, game);
	// draw_map(game);

	float fraction = PI / 3 / WIDTH;
	float	start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->window, game->img, 0, 0);
	return(0);
	
}

void	init_window(t_cub *cubed, t_data *game)
{
	init_game(cubed, game);
	mlx_hook(game->window, 2, 1L<<0, key_press, &game->player);
	mlx_hook(game->window, 3, 1L<<1, key_release, &game->player);
	mlx_loop_hook(game->mlx_ptr, draw_loop, game);
	mlx_loop(game->mlx_ptr);
}