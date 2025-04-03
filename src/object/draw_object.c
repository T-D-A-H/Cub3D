/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:10:33 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/03 15:03:40 by jaimesan         ###   ########.fr       */
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

void	search_object(t_cub *cub, t_object *object, int num_objects)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num_objects)
	{
		j = -1;
		while (++j < num_objects)
		{
			if (cub->p_positions[i].distance < cub->p_positions[j].distance)
			{
				object->temp = cub->p_positions[i];
				cub->p_positions[i] = cub->p_positions[j];
				cub->p_positions[j] = object->temp;
			}
		}
	}
}

void	objects_calcs(t_player *player, t_object *object, t_position *obj)
{
	object->obj_x = obj->x - player->x ;
	object->obj_y = obj->y - player->y ;
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

void	print_object(t_cub *cub, t_object *object)
{
	int			y;

	y = -1;
	if (object->transform_y > 0 && object->stripe > 0 && object->stripe < WIDTH)
	{
		y = object->draw_start_y;
		while (y < object->draw_end_y)
		{
			object->d = (y - object->draw_start_y) * cub->textures[4]->height;
			object->tex_y = ((object->d * cub->textures[4]->height)
					/ object->obj_height) / cub->textures[4]->height;
			object->color = cub->textures[4]->data[cub->textures[4]->width
				* object->tex_y + object->tex_x];
			if (object->color != cub->textures[4]->data[0])
				put_pixel(object->stripe, y, object->color, cub);
			y += 2;
		}
	}
}

void	draw_object(t_cub *cub, t_player *player, int num_objects)
{
	int			i;
	t_object	object;
	t_position	obj;

	i = -1;
	init_object(&object, player);
	search_object(cub, &object, num_objects);
	while (++i < num_objects)
	{
		obj = cub->p_positions[i];
		objects_calcs(player, &object, &obj);
		while (object.stripe < object.draw_end_x)
		{
			object.tex_x = (int)(cub->textures[4]->height
					* (object.stripe
						- (-object.obj_width / 2 + object.obj_screen_x))
					* cub->textures[4]->width / object.obj_width)
				/ cub->textures[4]->height;
			print_object(cub, &object);
			object.stripe += 1;
		}
	}
}
