/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/27 17:06:35 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	pos_wall_text(t_cub *cub, t_loop *loop, t_draw *draw)
{
	if (loop->side == 0)
		draw->wallx = cub->player->y / BLOCK + loop->perpWallDist
			* loop->rayDirY;
	else
		draw->wallx = cub->player->x / BLOCK + loop->perpWallDist
			* loop->rayDirX;
	draw->wallx -= floor(draw->wallx);
	if (loop->side == 0)
	{
		if (loop->rayDirX > 0)
			draw->texi = 3;
		else
			draw->texi = 2;
	}
	else
	{
		if (loop->rayDirY > 0)
			draw->texi = 1;
		else
			draw->texi = 0;
	}
}

void	coor_textures(t_cub *cub, t_loop *loop, t_draw *draw)
{
	draw->texture_x = (int)(draw->wallx
			* (double)cub->textures[draw->texi]->width);
	if (loop->side == 0 && loop->rayDirX > 0)
		loop->texX = cub->textures[draw->texi]->width - loop->texX - 1;
	if (loop->side == 1 && loop->rayDirY < 0)
		loop->texX = cub->textures[draw->texi]->width - loop->texX - 1;
	draw->step = 1.0 * cub->textures[draw->texi]->width
		/ loop->lineHeight;
	draw->texpos = (loop->drawStart - HEIGHT / 2 + loop->lineHeight / 2)
		* draw->step;
}

void	print_walls(t_cub *cub, t_loop *loop, t_draw *draw, int x)
{
	int	y;

	y = loop->drawStart - 1;
	while (++y < loop->drawEnd)
	{
		draw->texy = (int)draw->texpos
			% (cub->textures[draw->texi]->height);
		draw->texpos += draw->step;
		draw->color = cub->textures[draw->texi]
			->data[cub->textures[draw->texi]->height
			* draw->texy + draw->texture_x];
		if (y >= 0 && y < HEIGHT)
			put_pixel(x, y, draw->color, cub);
	}
}

void	draw_wall_with_texture(t_cub *cub, t_loop *loop, int x)
{
	t_draw	draw;

	// Calcular la posición de la pared en la textura
	// Para saber que textura coger segun la direccion
	pos_wall_text(cub, loop, &draw);
	// Calcular coordenadas de la textura
	coor_textures(cub, loop, &draw);
	// Printear la textura
	print_walls(cub, loop, &draw, x);
}

void	raycasting(t_cub *cubed, t_player *player, t_loop *loop)
{
	int	x;

	x = -1;
	init_loop(loop);
	while (++x < WIDTH)
	{
		init_ray(player, loop, x);
		get_raycast_steps(player, cubed->loop);
		get_raycast_hits(cubed, loop);
		init_start_end(loop);
		draw_wall_with_texture(cubed, loop, x);
		draw_3dmap(cubed, loop->drawStart, loop->drawEnd, x);
	}
}
