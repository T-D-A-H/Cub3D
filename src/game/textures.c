/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:53:12 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/10 13:02:20 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_cub *cub, char *path, int index)
{
	cub->textures[index]->img = mlx_xpm_file_to_image(cub->game->mlx, path,
			&cub->textures[index]->width,
			&cub->textures[index]->height);
	if (cub->textures[index]->img == NULL)
	{
		return (printf(ERR_LOAD_TEXTUE), exit(1));
	}
	cub->textures[index]->data = (int *)mlx_get_data_addr(
			cub->textures[index]->img,
			&cub->textures[index]->bpp,
			&cub->textures[index]->size_line,
			&cub->textures[index]->endian);
}

void	load_all_textures(t_cub *cub)
{
	int	i;

	i = -1;
	if (BONUS)
	{
		while (++i < MAX_TEXTURES)
		{
			cub->textures[i] = malloc(sizeof(t_texture));
			if (!cub->textures[i])
				return (printf(ERR_MALLOC), exit (1));
		}
		load_texture(cub, cub->tex_paths[0], 0);
		load_texture(cub, cub->tex_paths[1], 1);
		load_texture(cub, cub->tex_paths[2], 2);
		load_texture(cub, cub->tex_paths[3], 3);
		load_texture(cub, cub->tex_paths[4], 4);
		load_texture(cub, cub->tex_paths[5], 5);
		load_texture(cub, cub->tex_paths[6], 6);
		load_texture(cub, cub->tex_paths[7], 7);
		load_texture(cub, cub->tex_paths[8], 8);
		load_texture(cub, cub->tex_paths[9], 9);
		load_texture(cub, cub->tex_paths[10], 10);
		load_texture(cub, cub->tex_paths[11], 11);
		load_texture(cub, cub->tex_paths[12], 12);
		load_texture(cub, cub->tex_paths[13], 13);
		load_texture(cub, cub->tex_paths[14], 14);
		load_texture(cub, cub->tex_paths[15], 15);
		load_texture(cub, cub->tex_paths[16], 16);
		load_texture(cub, cub->tex_paths[17], 17);
		load_texture(cub, cub->tex_paths[18], 18);
		load_texture(cub, cub->tex_paths[19], 19);
		load_texture(cub, cub->tex_paths[20], 20);
	}
	else
	{
		while (++i < 4)
		{
			cub->textures[i] = malloc(sizeof(t_texture));
			if (!cub->textures[i])
				return (printf(ERR_MALLOC), exit (1));
		}
		load_texture(cub, cub->no_path, 0);
		load_texture(cub, cub->so_path, 1);
		load_texture(cub, cub->we_path, 2);
		load_texture(cub, cub->ea_path, 3);
	}
}

void	get_wall_textures(t_cub *cub, t_loop *loop, t_draw *draw)
{
	if (loop->side == 0)
		draw->wallx = cub->player->y / BLOCK + loop->perpwalldist
			* loop->raydir_y;
	else
		draw->wallx = cub->player->x / BLOCK + loop->perpwalldist
			* loop->raydir_x;
	draw->wallx -= floor(draw->wallx);
	if (loop->side == 0)
	{
		if (loop->raydir_x > 0)
			draw->texi = 2;
		else
			draw->texi = 3;
	}
	else
	{
		if (loop->raydir_y > 0)
			draw->texi = 1;
		else
			draw->texi = 0;
	}
	if (BONUS)
	{
		draw->texi_no_door = 1;
		draw->texi_door = 2;
		draw->texi_floor = 3;
		draw->texi_ceiling = 4;
		draw->texi = 5;
		if (cub->game->level == 1)
		{
			draw->texi = 10;
			draw->texi_floor = 8;
			draw->texi_ceiling = 9;
			draw->texi_door = 7;
			draw->texi_no_door = 6;
		}
		else if (cub->game->level == 2)
		{
			draw->texi = 15;
			draw->texi_floor = 13;
			draw->texi_ceiling = 15;
			draw->texi_door = 12;
			draw->texi_no_door = 11;
		}
		else if (cub->game->level == 3)
		{
			draw->texi = 20;
			draw->texi_floor = 18;
			draw->texi_ceiling = 19;
			draw->texi_door = 17;
			draw->texi_no_door = 16;
		}
		if (loop->door == 1)
			draw->texi = draw->texi_door;
	}
}

void	get_coor_textures(t_cub *cub, t_loop *loop, t_draw *draw)
{
	loop->texx = (int)(draw->wallx
			* (double)cub->textures[draw->texi]->width);
	if (loop->side == 0 && loop->raydir_x > 0)
		loop->texx = cub->textures[draw->texi]->width - loop->texx - 1;
	if (loop->side == 1 && loop->raydir_y < 0)
		loop->texx = cub->textures[draw->texi]->width - loop->texx - 1;
	draw->step = 1.0 * cub->textures[draw->texi]->width
		/ loop->line_height;
	draw->texpos = (loop->drawstart - HEIGHT / 2 + loop->line_height / 2)
		* draw->step;
}
