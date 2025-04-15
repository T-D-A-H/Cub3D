/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:48:56 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/15 12:50:37 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_struct(t_cub *cubed)
{
	cubed->no_path = NULL;
	cubed->so_path = NULL;
	cubed->we_path = NULL;
	cubed->ea_path = NULL;
	cubed->premap = NULL;
	cubed->map = NULL;
	cubed->pj_x = -1;
	cubed->pj_y = -1;
	cubed->start_direction = -1.0;
	cubed->p_count = -1;
	cubed->p_capacity = -1;
	cubed->blink_state = -1;
	cubed->blink_counter = -1;
	cubed->animation_counter = -1;
}

void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed)
{
	player->x = (double)((s_x * BLOCK)) + 32;
	player->y = (double)((s_y * BLOCK)) + 32;
	player->mx = (int)(player->x / BLOCK);
	player->my = (int)(player->y / BLOCK);
	player->dx = cos(player->angle) * 5;
	player->dy = sin(player->angle) * 5;
	player->angle = cubed->start_direction;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
	player->key_f = false;
	player->is_moving = false;
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
	loop->x = 0;
	loop->door = 0;
	loop->door_wall = 0;
}

void	init_object(t_object *object, t_player *player)
{
	object->inv_det = 0;
	object->transform_x = 0;
	object->transform_y = 0;
	object->obj_screen_x = 0;
	object->obj_height = 0;
	object->obj_width = 0;
	object->draw_start_y = 0;
	object->draw_end_y = 0;
	object->draw_start_x = 0;
	object->draw_end_x = 0;
	object->tex_x = 0;
	object->tex_y = 0;
	object->stripe = 0;
	object->obj_x = 0;
	object->obj_y = 0;
	object->fov = 0.66;
	object->plane_x = -player->dy * object->fov;
	object->plane_y = player->dx * object->fov;
	object->color = 0;
	object->d = 0;
}
