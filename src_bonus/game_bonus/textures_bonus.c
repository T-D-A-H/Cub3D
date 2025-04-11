/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:53:12 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/11 18:04:48 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
	while (++i < MAX_TEXTURES)
	{
		cub->textures[i] = malloc(sizeof(t_texture));
		if (!cub->textures[i])
			return (printf(ERR_MALLOC), exit (1));
		load_texture(cub, cub->tex_paths[i], i);
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
	draw->texi_no_door = (1 + (cub->game->level % 4 * 5));
	draw->texi_door = (2 + (cub->game->level % 4 * 5));
	draw->texi_floor = (3 + (cub->game->level % 4 * 5));
	draw->texi_ceiling = (4 + (cub->game->level % 4 * 5));
	draw->texi = (5 + (cub->game->level % 4 * 5));
	if (loop->door == 1)
		draw->texi = draw->texi_door;
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
