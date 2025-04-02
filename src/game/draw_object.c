/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:10:33 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/02 16:47:15 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double porcent_object(t_cub *cubed, t_loop *loop)
{
    int visible_samples;
    int total_samples;
	double block_y;
	double block_x;
	double tx;
	double ty;
	int visible;

	visible_samples = 0;
	total_samples = 0;
	block_x = loop->map_x * BLOCK + 0.1;
    while (block_x < (loop->map_x + 1) * BLOCK)
    {
        block_y = loop->map_y * BLOCK + 0.9;
        while (block_y < (loop->map_y + 1) * BLOCK)
        {
            total_samples++;
            tx = cubed->player->x;
			ty = cubed->player->y;
            visible = 1;

            while (sqrt(pow(tx - block_x, 2) + pow(ty - block_y, 2)) > 0.5)
            {
                tx += (block_x - cubed->player->x) * 0.05;
                ty += (block_y - cubed->player->y) * 0.05;

                if (cubed->map[(int)(ty / BLOCK)][(int)(tx / BLOCK)] == '1')
                {
                    visible = 0;
                    break;
                }
            }
            visible_samples += visible;
            block_y += BLOCK / 4 * 2;
        }
        block_x += (BLOCK / 4) * 2 ;
    }
    return ((double)visible_samples / total_samples);
}

void calcs_object(t_cub *cubed, t_loop *loop)
{
    int already_added;
    int k;

    if (porcent_object(cubed, loop) >= 0.6)
    {
        already_added = 0;
        k = 0;
        while (k++ < cubed->p_count)
        {
            if ((int)cubed->p_positions[k].x == (int)(loop->map_x * BLOCK + (BLOCK / 2))
            && (int)cubed->p_positions[k].y == (int)(loop->map_y * BLOCK + (BLOCK / 2)))
            {
                already_added = 1;
                break;
            }
        }
        if (!already_added && cubed->p_count < cubed->p_capacity)
        {
            t_position *pos = &cubed->p_positions[cubed->p_count];
            pos->x = loop->map_x * BLOCK + (BLOCK / 2);
            pos->y = loop->map_y * BLOCK + (BLOCK / 2);
            pos->distance = sqrt(pow(pos->x - cubed->player->x, 2) + pow(pos->y - cubed->player->y, 2));
            cubed->p_count++;
        }
    }
}

void draw_object(t_cub *cub, t_player *player, int num_objects)
{
	int i;
	double inv_det, transform_x, transform_y;
	int obj_screen_x;
	int obj_height, obj_width;
	int draw_start_y, draw_end_y;
	int draw_start_x, draw_end_x;
	int tex_x, tex_y;
	int stripe;

	double fov = 0.66;
	double plane_x = -player->dy * fov;
	double plane_y = player->dx * fov;

	for (int i = 0; i < num_objects; i++) {
		for (int j = i + 1; j < num_objects; j++) {
			if (cub->p_positions[i].distance < cub->p_positions[j].distance) {
				t_position temp = cub->p_positions[i];
				cub->p_positions[i] = cub->p_positions[j];
				cub->p_positions[j] = temp;
			}
		}
	}

	for (i = 0; i < num_objects; i++) {
		t_position obj = cub->p_positions[i];
		double obj_x = obj.x - player->x ;
		double obj_y = obj.y - player->y ;
   		double angle_to_obj = atan2(obj_y, obj_x);
		double angle_diff = fabs(fmod(player->angle - angle_to_obj + 5*PI, 2*PI) - PI);
		if (angle_diff > PI/6)
		continue;

		inv_det = 1.0 / (plane_x * player->dy - player->dx * plane_y);
		transform_x = inv_det * (player->dy * obj_x - player->dx * obj_y);
		transform_y = inv_det * (-plane_y * obj_x + plane_x * obj_y);
		obj_screen_x = (int)(WIDTH / 2) * (1 + transform_x / transform_y);
		obj_height = ((int)(HEIGHT / (transform_y) * 5));

		draw_start_y = (HEIGHT / 2) + (int)(0.05 * HEIGHT) + (int)(HEIGHT / transform_y);
		draw_end_y = draw_start_y + obj_height;
		if (draw_start_y > HEIGHT * 0.8)
			draw_start_y = HEIGHT * 0.8;

		obj_width = abs((int)(HEIGHT / (transform_y / 5)));
		draw_start_x = -obj_width / 2 + obj_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = draw_start_x + obj_width;
		if (draw_end_x >= WIDTH)
			draw_end_x = WIDTH - 1;

		for (stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			tex_x = (int)(16 * (stripe - (-obj_width / 2 + obj_screen_x)) * cub->textures[4]->width / obj_width) / 16;
			if (transform_y > 0 && stripe > 0 && stripe < WIDTH)
			{
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = (y - draw_start_y) * 16;
					tex_y = ((d * cub->textures[4]->height) / obj_height) / 16;
					int color = cub->textures[4]->data[cub->textures[4]->width * tex_y + tex_x];
					if (color != cub->textures[4]->data[0]) {
						put_pixel(stripe, y, color, cub);
					}
					y += 1;
				}
			}
		}
	}
}