/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:01:38 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/15 15:18:12 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window(t_cub *cubed)
{
	error(cubed, NO_ERROR, 1);
	return (0);
}

void	free_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (cub->textures[i])
		{
			if (cub->textures[i]->img)
				mlx_destroy_image(cub->game->mlx, cub->textures[i]->img);
			free(cub->textures[i]);
		}
		i++;
	}
}

void	free_tex_paths(t_cub *cubed)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (cubed->tex_paths[i])
		{
			free(cubed->tex_paths[i]);
			cubed->tex_paths[i] = NULL;
		}
		i++;
	}
}

void	error(t_cub *cubed, char *debug_msg, int signal)
{
	printf("%s", debug_msg);
	if (cubed->no_path)
		free(cubed->no_path);
	if (cubed->so_path)
		free(cubed->so_path);
	if (cubed->we_path)
		free(cubed->we_path);
	if (cubed->ea_path)
		free(cubed->ea_path);
	if (cubed->map)
		ft_freearr(cubed->map);
	if (cubed->premap)
		free(cubed->premap);
	if (cubed->tex_paths[0] != NULL)
		free_tex_paths(cubed);
	if (signal == 1 && cubed->game->img)
		mlx_destroy_image(cubed->game->mlx, cubed->game->img);
	if (signal == 1 && cubed->game->win)
		mlx_destroy_window(cubed->game->mlx, cubed->game->win);
	if (signal == 1)
		free_textures(cubed);
	if (!debug_msg[0])
		exit(0);
	exit(signal);
}
