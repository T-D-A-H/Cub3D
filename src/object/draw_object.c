/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:10:33 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/09 15:01:17 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	sort_objects_by_distance(t_position *objects, int num_objects)
{
	int			i;
	int			j;
	t_position	temp;

	i = -1;
	while (++i < num_objects)
	{
		j = -1;
		while (++j < num_objects)
		{
			if (objects[i].distance < objects[j].distance)
			{
				temp = objects[i];
				objects[i] = objects[j];
				objects[j] = temp;
			}
		}
	}
}

void	objects_calcs(t_player *player, t_object *object, t_position *obj)
{
	object->obj_x = obj->x - player->x;
	object->obj_y = obj->y - player->y;
	object->inv_det = 1.0 / (object->plane_x
			* player->dy - player->dx * object->plane_y);
	object->transform_x = object->inv_det
		* (player->dy * object->obj_x - player->dx * object->obj_y);
	object->transform_y = object->inv_det
		* (-object->plane_y * object->obj_x + object->plane_x * object->obj_y);
	object->obj_screen_x = (int)(WIDTH / 2)
		*(1 + object->transform_x / object->transform_y);
	object->obj_height = ((int)(HEIGHT / (object->transform_y) * 5));
	object->draw_start_y = (HEIGHT / 2) + (int)(0.05 * HEIGHT)
		+ (int)(HEIGHT / object->transform_y);
	object->draw_end_y = object->draw_start_y + object->obj_height;
	object->obj_width = abs((int)(HEIGHT / (object->transform_y / 5)));
	object->draw_start_x = -object->obj_width / 2 + object->obj_screen_x;
	object->draw_end_x = object->draw_start_x + object->obj_width;
	object->stripe = object->draw_start_x;
}

void	draw_object(t_cub *cub, t_player *player,
	int num_objects, t_position *obj)
{
	int			i;
	t_object	object;

	init_object(&object, player);
	i = -1;
	while (++i < num_objects)
	{
		obj = &cub->p_positions[i];
		obj->distance = sqrt(pow(player->x - obj->x, 2)
				+ pow(player->y - obj->y, 2));
		if (cub->game->level == 1 || cub->game->level == 2
			|| cub->game->level == 3)
			obj[i].is_taken = 0;
		if (obj[i].is_taken == 0)
		{
			check_object_pickup(cub, player, &obj[i]);
			if (obj[i].is_taken == 0)
			{
				objects_calcs(player, &object, &obj[i]);
				print_obj_calcs(cub, &object);
			}
		}
	}
}
