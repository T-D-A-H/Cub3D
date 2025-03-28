/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:27:17 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/28 13:06:23 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		else if (cubed->map[loop->map_y][loop->map_x] == '1' ||
			cubed->map[loop->map_y][loop->map_x] == ' ')
			loop->hit = 1;
	}
}

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

void	init_start_end(t_loop *loop)
{
	if (loop->side == 0)
		loop->perpwalldist = (loop->sidedist_x - loop->deltadist_x);
	else
		loop->perpwalldist = (loop->sidedist_y - loop->deltadist_y);
	loop->line_height = (int)(HEIGHT / loop->perpwalldist);
	loop->drawstart = -loop->line_height / 2 + HEIGHT / 2;
	if (loop->drawstart < 0)
		loop->drawstart = 0;
	loop->drawend = loop->line_height / 2 + HEIGHT / 2;
	if (loop->drawend >= HEIGHT)
		loop->drawend = HEIGHT - 1;
}
