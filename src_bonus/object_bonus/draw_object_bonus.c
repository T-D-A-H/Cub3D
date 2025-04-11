/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:10:33 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/11 17:03:25 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

void	objects_calcs(t_player *player, t_object *object,
	t_position *obj, int counter)
{
	object->animation_speed = 0.07;
	object->animation_range = 0.02;
	object->screen_vertical_offset = sinf(counter * object->animation_speed)
		* object->animation_range * HEIGHT;
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
	object->draw_start_y += (int)object->screen_vertical_offset;
	object->draw_end_y += (int)object->screen_vertical_offset;
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
		obj = &cub->p_pos[i];
		obj->distance = sqrt(pow(player->x - obj->x, 2)
				+ pow(player->y - obj->y, 2));
		obj[i].is_taken = 0;
		if (obj[i].is_taken == 0)
		{
			check_object_pickup(cub, player, &obj[i]);
			if (obj[i].is_taken == 0)
			{
				objects_calcs(player, &object, &obj[i], cub->animation_counter);
				print_obj_calcs(cub, &object);
			}
		}
	}
}
