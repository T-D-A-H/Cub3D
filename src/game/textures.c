/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:53:12 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/27 15:56:00 by jaimesan         ###   ########.fr       */
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
		return (printf(ERR_LOAD_TEXTUE), exit (1));
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
