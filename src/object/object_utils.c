/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:57:57 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/03 15:04:04 by jaimesan         ###   ########.fr       */
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
	block_x = loop->map_x * BLOCK + 0.5;
    while (block_x < (loop->map_x + 1) * BLOCK)
    {
        block_y = loop->map_y * BLOCK + 0.5;
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
            block_y += BLOCK / 4 ;
        }
        block_x += (BLOCK / 4)  ;
    }
    return ((double)visible_samples / total_samples);
}

void calcs_object(t_cub *cubed, t_loop *loop)
{
    int	already_added;
    int	k;

    if (porcent_object(cubed, loop) >= 0.5)
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
