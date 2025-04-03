/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:55:37 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/03 14:07:23 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int door_is_closed(t_cub *cubed, t_player *player)
{
    int map_x;
    int map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
    if (cubed->map[map_y + 1][map_x] == 'D' || cubed->map[map_y][map_x + 1] == 'D' 
		|| cubed->map[map_y - 1][map_x] == 'D' || cubed->map[map_y][map_x - 1] == 'D')
	{
		return (1);
    }
	return (0);
}

void open_door(t_cub *cubed, t_player *player)
{
    int map_x;
    int map_y;

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
			cubed->map[map_y + 1][map_x]  = 'd';
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

void	get_texture_data(t_cub *cubed, t_loop *loop, t_texture *tex)
{
	if (tex->side == 0)
		tex->perpwalldist = (tex->sidedist_xy[1] - loop->deltadist_y);
	else
		tex->perpwalldist = (tex->sidedist_xy[0] - loop->deltadist_x);
	tex->line_height = (int)(HEIGHT / tex->perpwalldist);
	tex->drawstart = -tex->line_height / 2 + HEIGHT / 2;
	if (tex->drawstart < 0)
		tex->drawstart = 0;
	tex->drawend = tex->line_height / 2 + HEIGHT / 2;
	if (tex->drawend >= HEIGHT)
		tex->drawend = HEIGHT - 1;
	if (tex->side == 0)
		tex->wallx = cubed->player->x / BLOCK + tex->perpwalldist * loop->raydir_x;
	else
		tex->wallx = cubed->player->y / BLOCK + tex->perpwalldist * loop->raydir_y;
	tex->wallx -= floor(tex->wallx);
	tex->texx = (int)(tex->wallx * (double)tex->width);
	if (tex->side == 0 && loop->raydir_x > 0)
		tex->texx = tex->width - tex->texx - 1;
	if (tex->side == 1 && loop->raydir_y < 0)
		tex->texx = tex->height - tex->texx - 1;
	tex->step = 1.0 * tex->width / tex->line_height;
	tex->texpos = (tex->drawstart - HEIGHT / 2 + tex->line_height / 2) * tex->step;
	tex->tex_id = 4;
}

void	get_texture_data2(t_cub *cubed, t_loop *loop, t_texture *tex)
{
	if (tex->side == 0)
		tex->perpwalldist = (tex->sidedist_xy[0] - loop->deltadist_x);
	else
		tex->perpwalldist = (tex->sidedist_xy[1] - loop->deltadist_y);
	tex->line_height = (int)(HEIGHT / tex->perpwalldist);
	tex->drawstart = -tex->line_height / 2 + HEIGHT / 2;
	if (tex->drawstart < 0)
		tex->drawstart = 0;
	tex->drawend = tex->line_height / 2 + HEIGHT / 2;
	if (tex->drawend >= HEIGHT)
		tex->drawend = HEIGHT - 1;
	if (tex->side == 0)
		tex->wallx = cubed->player->y / BLOCK + tex->perpwalldist * loop->raydir_y;
	else
		tex->wallx = cubed->player->x / BLOCK + tex->perpwalldist * loop->raydir_x;
	tex->wallx -= floor(tex->wallx);
	tex->texx = (int)(tex->wallx * (double)tex->width);
	if (tex->side == 0 && loop->raydir_x > 0)
		tex->texx = tex->width - tex->texx - 1;
	if (tex->side == 1 && loop->raydir_y < 0)
		tex->texx = tex->height - tex->texx - 1;
	tex->step = 1.0 * tex->width / tex->line_height;
	tex->texpos = (tex->drawstart - HEIGHT / 2 + tex->line_height / 2) * tex->step;
	tex->tex_id = 4;
}

void	render_objects(t_cub *cubed, int x)
{
	cubed->player->key_f = false;
	get_texture_data(cubed, cubed->loop, cubed->textures[4]);
	draw_wall_no_door(cubed, cubed->textures[4], x);
	get_texture_data2(cubed, cubed->loop, cubed->textures[4]);
	draw_wall_no_door(cubed, cubed->textures[4], x);
		
}
