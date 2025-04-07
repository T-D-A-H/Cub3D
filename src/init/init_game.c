/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/07 17:05:05 by jaimesan         ###   ########.fr       */
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
	player->x = (double)((s_x * BLOCK));
	player->y = (double)((s_y * BLOCK));
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
}

void draw_red_dot(t_cub *cubed)
{
	int center_x;
	int center_y;
	int y;
	int x;

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
			x+=1;
		}
		y+=2;
	}
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
    char *data_copy;
    int bytes_per_pixel;

    if (!cubed || !cubed->game)
        return;

    // Crear una copia de los datos de la imagen original
    bytes_per_pixel = cubed->game->bpp / 8;
    data_copy = malloc(cubed->game->size_line * HEIGHT);

	
    frame_counter++;
    scan_line = (scan_line + 1) % HEIGHT;

    // Aplicar efectos cada 2 frames para mejor rendimiento
    if (frame_counter % 2 != 0)
        return;

    // Efecto de ruido y líneas de escaneo
    for (y = 0; y < HEIGHT; y++)
    {
        // Ruido aleatorio (25% de probabilidad por línea)
        if (rand() % 2 == 0)
        {
            int noise = rand() % 50 - 25;
            for (x = 0; x < WIDTH; x += (rand() % 3 + 1)) // Saltos aleatorios
            {
                color = get_pixel_color(x, y, cubed);
                int r = (color >> 16) & 0xFF;
                int g = (color >> 8) & 0xFF;
                int b = color & 0xFF;

                // Añadir ruido con límites seguros
                r = (r + noise) % 256;
                g = (g + noise) % 256;
                b = (b + noise + 15) % 256; // Más azul para efecto VHS

                if (r < 0) r = 0;
                if (g < 0) g = 0;
                if (b < 0) b = 0;

                put_pixel(x, y, (r << 16) | (g << 8) | b, cubed);
            }
        }

        // Línea de escaneo más visible
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
	cubed->blink_counter++;
	if (cubed->blink_counter > 10)
	{
		cubed->blink_counter = 0;
		cubed->blink_state = !cubed->blink_state;
	}
	clear_screen(cubed);
	move_player(cubed->player, cubed);
	raycasting(cubed, cubed->player, cubed->loop);
	apply_vhs_effect(cubed);
	if (BONUS == 1)
	{
		if (cubed->blink_state == 1)
			draw_red_dot(cubed);
		draw_minimap(cubed);
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

void	init_window(t_cub *cubed)
{
	init_objects(cubed);
	init_player(cubed->player, cubed->pj_x, cubed->pj_y, cubed);
	init_game(cubed->game, cubed);
	mlx_hook(cubed->game->win, 2, 1L << 0, on_keypress, cubed);
	mlx_hook(cubed->game->win, 3, 1L << 1, on_keyrelease, cubed->player);
	mlx_loop_hook(cubed->game->mlx, game_loop, cubed);
	mlx_loop(cubed->game->mlx);
}
