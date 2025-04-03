/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:57:57 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/03 16:34:39 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_porcent_object(t_loop *loop, t_object_porc *porc)
{
	porc->visible_samples = 0;
	porc->total_samples = 0;
	porc->block_x = loop->map_x * BLOCK + 0.5;
}

void	porcent_object_cals(t_cub *cub, t_loop *loop, t_object_porc *po)
{
	po->block_y = loop->map_y * BLOCK + 0.5;
	while (po->block_y < (loop->map_y + 1) * BLOCK)
	{
		po->total_samples++;
		po->tx = cub->player->x;
		po->ty = cub->player->y;
		po->visible = 1;
		while (sqrt(pow(po->tx - po->block_x, 2)
				+ pow(po->ty - po->block_y, 2)) > 0.5)
		{
			po->tx += (po->block_x - cub->player->x) * 0.05;
			po->ty += (po->block_y - cub->player->y) * 0.05;
			if (cub->map[(int)(po->ty / BLOCK)][(int)(po->tx / BLOCK)] == '1')
			{
				po->visible = 0;
				break ;
			}
		}
		po->visible_samples += po->visible;
		po->block_y += BLOCK / 4;
	}
	po->block_x += (BLOCK / 4);
}

double	porcent_object(t_cub *cubed, t_loop *loop)
{
	t_object_porc	porc;

	init_porcent_object(loop, &porc);
	while (porc.block_x < (loop->map_x + 1) * BLOCK)
		porcent_object_cals(cubed, loop, &porc);
	return ((double)porc.visible_samples / porc.total_samples);
}

void	check_is_added(t_cub *cubed, t_loop *loop, int *already_added, int *k)
{
	while ((*k)++ < cubed->p_count)
	{
		if ((int)cubed->p_positions[*k].x
			== (int)(loop->map_x * BLOCK + (BLOCK / 2))
		&& (int)cubed->p_positions[*k].y
			== (int)(loop->map_y * BLOCK + (BLOCK / 2)))
		{
			*already_added = 1;
			break ;
		}
	}
}

void	calcs_object(t_cub *cubed, t_loop *loop)
{
	t_position	*pos;
	int			already_added;
	int			k;

	if (porcent_object(cubed, loop) >= 0.5)
	{
		already_added = 0;
		k = 0;
		check_is_added(cubed, loop, &already_added, &k);
		if (!already_added && cubed->p_count < cubed->p_capacity)
		{
			pos = &cubed->p_positions[cubed->p_count];
			pos->x = loop->map_x * BLOCK + (BLOCK / 2);
			pos->y = loop->map_y * BLOCK + (BLOCK / 2);
			pos->distance = sqrt(pow(pos->x - cubed->player->x, 2)
					+ pow(pos->y - cubed->player->y, 2));
			cubed->p_count++;
		}
	}
}
