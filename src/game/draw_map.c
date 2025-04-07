/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:27:17 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/07 15:15:30 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	draw_ceiling(t_cub *cub, t_loop *loop, int x, int y)
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	while (y < loop->drawstart)
	{
		row_distance = HEIGHT / (2.0 * y - HEIGHT);
		floor_x = cub->player->x / BLOCK - row_distance * loop->raydir_x;
		floor_y = cub->player->y / BLOCK - row_distance * loop->raydir_y;
		tex_x = (int)(floor_x * cub->textures[2]->width)
			% cub->textures[2]->width;
		tex_y = (int)(floor_y * cub->textures[2]->height)
			% cub->textures[2]->height;
		put_pixel(x, y, cub->textures[2]->data[tex_y
			* cub->textures[2]->width + tex_x], cub);
		y++;
	}
}

void	draw_floor(t_cub *cub, t_loop *loop, int x, int y)
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	while (y < HEIGHT)
	{
		row_distance = HEIGHT / (2.0 * y - HEIGHT);
		floor_x = cub->player->x / BLOCK + row_distance * loop->raydir_x;
		floor_y = cub->player->y / BLOCK + row_distance * loop->raydir_y;
		tex_x = (int)(floor_x * cub->textures[1]->width)
			% cub->textures[1]->width;
		tex_y = (int)(floor_y * cub->textures[1]->height)
			% cub->textures[1]->height;
		put_pixel(x, y, cub->textures[1]->data[tex_y
			* cub->textures[1]->width + tex_x], cub);
		y++;
	}
}

void	draw_walls(t_cub *cub, t_loop *loop, t_draw *draw, int x)
{
	int	y;

	y = loop->drawstart - 1;
	while (++y < loop->drawend)
	{
		draw->texy = (int)draw->texpos
			% (cub->textures[draw->texi]->height);
		draw->texpos += draw->step;
		draw->color = cub->textures[draw->texi]
			->data[cub->textures[draw->texi]->height * draw->texy + loop->texx];
		if (y >= 0 && y < HEIGHT)
		{
			put_pixel(x, y, draw->color, cub);
		}
	}
}
