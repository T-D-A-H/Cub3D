/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:01:38 by ctommasi          #+#    #+#             */
/*   Updated: 2025/05/02 17:08:49 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	free_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (cub->textures[i])
		{
			if (cub->textures[i]->img)
			{
				mlx_destroy_image(cub->game->mlx, cub->textures[i]->img);
			}
			if (cub->textures[i])
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
	cubed->is_running = 0;
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
	if (signal == 1 && cubed->p_pos)
		free(cubed->p_pos);
	if (signal == 1)
		free_textures(cubed);
	exit(signal);
}
