/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/01 14:47:02 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_player *player, t_loop *loop, int x)
{
	loop->ray_angle = player->angle - (PI / 6) + (x * loop->fov);
	loop->raydir_x = cos(loop->ray_angle);
	loop->raydir_y = sin(loop->ray_angle);
	loop->deltadist_x = fabs(1 / loop->raydir_x);
	loop->deltadist_y = fabs(1 / loop->raydir_y);
	loop->map_x = player->mx;
	loop->map_y = player->my;
}

void	init_loop(t_loop *loop)
{
	loop->fov = PI / 3 / WIDTH;
	loop->ray_angle = 0;
	loop->raydir_x = 0;
	loop->raydir_y = 0;
	loop->sidedist_x = 0;
	loop->sidedist_y = 0;
	loop->map_x = 0;
	loop->map_y = 0;
	loop->deltadist_x = 0;
	loop->deltadist_y = 0;
	loop->step_x = 0;
	loop->step_y = 0;
	loop->hit = 0;
	loop->side = 0;
	loop->perpwalldist = 0;
	loop->line_height = 0;
	loop->drawstart = 0;
	loop->drawend = 0;
	loop->x = -1;
}

void	get_raycast_steps(t_player *player, t_loop *loop)
{
	if (loop->raydir_x < 0)
	{
		loop->step_x = -1;
		loop->sidedist_x = ((player->x / BLOCK) - loop->map_x)
			* loop->deltadist_x;
	}
	else
	{
		loop->step_x = 1;
		loop->sidedist_x = ((loop->map_x + 1.0) - (player->x / BLOCK))
			* loop->deltadist_x;
	}
	if (loop->raydir_y < 0)
	{
		loop->step_y = -1;
		loop->sidedist_y = ((player->y / BLOCK) - loop->map_y)
			* loop->deltadist_y;
	}
	else
	{
		loop->step_y = 1;
		loop->sidedist_y = ((loop->map_y + 1.0) - (player->y / BLOCK))
			* loop->deltadist_y;
	}
}

void	get_raycast_hits(t_cub *cubed, t_loop *loop)
{
	loop->hit = 0;
	while (loop->hit == 0)
	{
		if (loop->sidedist_x < loop->sidedist_y)
		{
			loop->sidedist_x += loop->deltadist_x;
			loop->map_x += loop->step_x;
			loop->side = 0;
		}
		else
		{
			loop->sidedist_y += loop->deltadist_y;
			loop->map_y += loop->step_y;
			loop->side = 1;
		}
		if (loop->map_y < 0 || loop->map_x < 0
			|| loop->map_y >= HEIGHT / BLOCK || loop->map_x >= WIDTH / BLOCK)
			break ;
		else if (cubed->map[loop->map_y][loop->map_x] == '1'
			|| cubed->map[loop->map_y][loop->map_x] == ' ')
			loop->hit = 1;
		else if (cubed->map[loop->map_y][loop->map_x] == 'D' && BONUS == 1)
		{
			loop->hit = 1;
			loop->door = 1;
		}
	}
}

void	raycasting(t_cub *cubed, t_player *player, t_loop *loop)
{
	t_draw	draw;

	init_loop(loop);
	while (++loop->x < WIDTH)
	{
		loop->door = 0;
		init_ray(player, loop, loop->x);
		get_raycast_steps(player, cubed->loop);
		get_raycast_hits(cubed, loop);
		init_start_end(loop);
		get_wall_textures(cubed, loop, &draw);
		get_coor_textures(cubed, loop, &draw);
		if (BONUS)
		{
			draw_walls(cubed, loop, &draw, loop->x);
			draw_ceiling(cubed, loop, loop->x, 0);
			draw_floor(cubed, loop, loop->x, loop->drawend);
			if (cubed->player->key_f)
			{
				handle_door_interaction(cubed, player);
				cubed->player->key_f = false;
			}
		}
		else
		{
			draw_3dmap(cubed, loop->drawstart, loop->drawend, loop->x);
			draw_walls(cubed, cubed->loop, &draw, loop->x);
		}
		loop->x += 1;
	}
}
