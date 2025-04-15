/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:00:05 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/15 13:06:35 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
	cubed->animation_counter++;
	if (cubed->blink_state == 1)
		draw_red_dot(cubed);
	apply_vhs_effect(cubed);
	if (PRO)
		draw_minimap(cubed);
	mlx_put_image_to_window(cubed->game->mlx, cubed->game->win,
		cubed->game->img, 0, 0);
	return (0);
}

void	init_window(t_game *game, t_cub *cubed)
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

void	init_objects(t_cub *cubed)
{
	cubed->animation_counter = 0;
	cubed->game->action_done = 0;
	cubed->p_capacity = 50;
	cubed->p_pos = malloc(sizeof(t_position) * cubed->p_capacity);
	if (!cubed->p_pos)
		error(cubed, ERR_MALLOC, 1);
	cubed->p_count = 0;
}

void	init_game(t_cub *cubed)
{
	cubed->game->level = 0;
	init_objects(cubed);
	init_player(cubed->player, cubed->pj_x, cubed->pj_y, cubed);
	init_sounds(cubed);
	init_window(cubed->game, cubed);
	mlx_hook(cubed->game->win, 2, 1L << 0, on_keypress, cubed);
	mlx_hook(cubed->game->win, 3, 1L << 1, on_keyrelease, cubed->player);
	mlx_mouse_hide(cubed->game->mlx, cubed->game->win);
	mlx_mouse_move(cubed->game->mlx, cubed->game->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(cubed->game->win, 6, 1L << 6, mouse_move, cubed);
	mlx_loop_hook(cubed->game->mlx, game_loop, cubed);
	mlx_loop(cubed->game->mlx);
	mlx_mouse_show(cubed->game->mlx, cubed->game->win);
}
