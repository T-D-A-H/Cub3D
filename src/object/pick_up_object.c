/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_up_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:40:07 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/08 15:02:08 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_object(t_cub *cub, t_object *object)
{
	int			y;

	y = -1;
	if (object->transform_y > 0 && object->stripe > 0 && object->stripe < WIDTH)
	{
		y = object->draw_start_y;
		while (y < object->draw_end_y)
		{
			object->d = (y - object->draw_start_y) * cub->textures[0]->height;
			object->tex_y = ((object->d * cub->textures[0]->height)
					/ object->obj_height) / cub->textures[0]->height;
			object->color = cub->textures[0]->data[cub->textures[0]->width
				* object->tex_y + object->tex_x];
			if (object->color != cub->textures[0]->data[0])
				put_pixel(object->stripe, y, object->color, cub);
			y += 2;
		}
	}
}

void	check_object_pickup(t_cub *cub, t_player *player, t_position *obj)
{
	double	distance;
	int		map_x;
	int		map_y;

	distance = sqrt(pow(player->x - obj->x, 2)
			+ pow(player->y - obj->y, 2));
	if (distance < 50.0)
	{
		map_x = (int)(obj->x / BLOCK);
		map_y = (int)(obj->y / BLOCK);
		if (map_x >= 0 && map_x < WIDTH
			&& map_y >= 0 && map_y < HEIGHT
			&& cub->map[map_y][map_x] == 'O')
		{
			cub->map[map_y][map_x] = '0';
			obj->is_taken = 1;
		}
	}
}

void	print_obj_calcs(t_cub *cub, t_object *object)
{
	while (object->stripe < object->draw_end_x)
	{
		object->tex_x = (int)(cub->textures[0]->height
				* (object->stripe - (-object->obj_width / 2
						+ object->obj_screen_x))
				* cub->textures[0]->width / object->obj_width)
			/ cub->textures[0]->height;
		print_object(cub, object);
		object->stripe += 1;
	}
}
