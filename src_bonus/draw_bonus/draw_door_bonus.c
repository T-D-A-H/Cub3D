/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:55:37 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/11 17:29:19 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_wall_no_door(t_cub *cub, t_texture *tex, int x)
{
	int	y;

	y = tex->drawstart - 1;
	while (++y < tex->drawend)
	{
		tex->texy = (int)tex->texpos % tex->height;
		tex->texpos += tex->step;
		tex->color = tex->data[tex->height * tex->texy + tex->texx];
		if (y >= 0 && y < HEIGHT)
		{
			if (tex->color != 0x000000 && tex->color != 0)
				put_pixel(x, y, tex->color, cub);
		}
	}
}

void	wall_coords(t_cub *cubed, t_texture *tex, int mode, int tex_id)
{
	if (tex->side == 0 && mode == 0)
		tex->wallx = cubed->player->x / BLOCK + tex->perpwalldist
			* cubed->loop->raydir_x;
	else if (mode == 0)
		tex->wallx = cubed->player->y / BLOCK + tex->perpwalldist
			* cubed->loop->raydir_y;
	else if (tex->side == 0 && mode == 1)
		tex->wallx = cubed->player->y / BLOCK + tex->perpwalldist
			* cubed->loop->raydir_y;
	else if (mode == 1)
		tex->wallx = cubed->player->x / BLOCK + tex->perpwalldist
			* cubed->loop->raydir_x;
	tex->wallx -= floor(tex->wallx);
	tex->texx = (int)(tex->wallx * (double)tex->width);
	if (tex->side == 0 && cubed->loop->raydir_x > 0)
		tex->texx = tex->width - tex->texx - 1;
	if (tex->side == 1 && cubed->loop->raydir_y < 0)
		tex->texx = tex->height - tex->texx - 1;
	tex->step = 1.0 * tex->width / tex->line_height;
	tex->texpos = (tex->drawstart - HEIGHT / 2 + tex->line_height / 2)
		* tex->step;
	tex->tex_id = tex_id;
}

void	init_start_end_wall(t_loop *loop, t_texture *tex, int mode)
{
	if (tex->side == 0 && mode == 0)
		tex->perpwalldist = (tex->sidedist_xy[1] - loop->deltadist_y);
	else if (mode == 0)
		tex->perpwalldist = (tex->sidedist_xy[0] - loop->deltadist_x);
	else if (tex->side == 0 && mode == 1)
		tex->perpwalldist = (tex->sidedist_xy[0] - loop->deltadist_x);
	else if (mode == 1)
		tex->perpwalldist = (tex->sidedist_xy[1] - loop->deltadist_y);
	tex->line_height = (int)(HEIGHT / tex->perpwalldist);
	tex->drawstart = -tex->line_height / 2 + HEIGHT / 2;
	if (tex->drawstart < 0)
		tex->drawstart = 0;
	tex->drawend = tex->line_height / 2 + HEIGHT / 2;
	if (tex->drawend >= HEIGHT)
		tex->drawend = HEIGHT - 1;
}

void	draw_door(t_cub *cub, t_loop *loop, int x, t_draw *draw)
{
	if (loop->door_wall)
	{
		init_start_end_wall(loop, cub->textures[draw->texi_no_door], 0);
		wall_coords(cub, cub->textures[draw->texi_no_door],
			0, draw->texi_no_door);
		draw_wall_no_door(cub, cub->textures[draw->texi_no_door], x);
		init_start_end_wall(loop, cub->textures[draw->texi_no_door], 1);
		wall_coords(cub, cub->textures[draw->texi_no_door],
			1, draw->texi_no_door);
		draw_wall_no_door(cub, cub->textures[draw->texi_no_door], x);
		if (cub->game->sees_door == 1 && !cub->game->action_done
			&& cub->map[cub->player->my][cub->player->mx] != 'd')
		{
			if (cub->map[cub->player->my - 1][cub->player->mx] == '0')
				cub->map[cub->player->my - 1][cub->player->mx] = '1';
			if (cub->map[cub->player->my + 1][cub->player->mx] == '0')
				cub->map[cub->player->my + 1][cub->player->mx] = '1';
			if (cub->map[cub->player->my][cub->player->mx - 1] == '0')
				cub->map[cub->player->my][cub->player->mx - 1] = '1';
			if (cub->map[cub->player->my][cub->player->mx + 1] == '0')
				cub->map[cub->player->my][cub->player->mx + 1] = '1';
			cub->game->action_done = 1;
		}
	}
	handle_door(cub, cub->player, cub->game);
}
