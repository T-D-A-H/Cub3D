/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:55:37 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/08 17:10:47 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	open_door(t_cub *cubed, t_player *player)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
	if (cubed->map[map_y + 1][map_x] == 'D'
		|| cubed->map[map_y][map_x + 1] == 'D'
		|| cubed->map[map_y - 1][map_x] == 'D'
		|| cubed->map[map_y][map_x - 1] == 'D')
	{
		if (cubed->map[map_y - 1][map_x] == 'D')
			cubed->map[map_y - 1][map_x] = 'd';
		else if (cubed->map[map_y + 1][map_x] == 'D')
			cubed->map[map_y + 1][map_x] = 'd';
		else if (cubed->map[map_y][map_x + 1] == 'D')
			cubed->map[map_y][map_x + 1] = 'd';
		else if (cubed->map[map_y][map_x - 1] == 'D')
			cubed->map[map_y][map_x - 1] = 'd';
		cubed->loop->door_wall = 1;
	}
}

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

void	get_wall_text_coords(t_cub *cubed, t_texture *tex, int mode, int tex_id)
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

void	draw_door(t_cub *cubed, int x)
{
	if (cubed->loop->door_wall)
	{
		init_start_end_wall(cubed->loop, cubed->textures[4], 0);
		get_wall_text_coords(cubed, cubed->textures[4], 0, 4);
		draw_wall_no_door(cubed, cubed->textures[4], x);
		init_start_end_wall(cubed->loop, cubed->textures[4], 1);
		get_wall_text_coords(cubed, cubed->textures[4], 1, 4);
		draw_wall_no_door(cubed, cubed->textures[4], x);
		if (cubed->game->sees_door == 1 && cubed->map[cubed->player->my][cubed->player->mx] != 'd')
		{
			if (cubed->map[cubed->player->my - 1][cubed->player->mx] == '0')
				cubed->map[cubed->player->my - 1][cubed->player->mx] = '1';
			else if (cubed->map[cubed->player->my + 1][cubed->player->mx] == '0')
				cubed->map[cubed->player->my + 1][cubed->player->mx] = '1';
			if (cubed->map[cubed->player->my][cubed->player->mx - 1] == '0')
				cubed->map[cubed->player->my][cubed->player->mx - 1] = '1';
			else if (cubed->map[cubed->player->my][cubed->player->mx + 1] == '0')
				cubed->map[cubed->player->my][cubed->player->mx + 1] = '1';
		}
	}
	handle_door(cubed, cubed->player, cubed->game);
}
