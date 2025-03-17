/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:01:38 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/17 12:51:12 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	error(t_cub *cubed, char *debug_msg)
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
	if (cubed->f_color)
		free(cubed->f_color);
	if (cubed->c_color)
		free(cubed->c_color);
	if (cubed->map)
		ft_freearr(cubed->map);
	if (cubed->premap)
		free(cubed->premap);
	if (!debug_msg[0])
		exit(0);
	else
		exit(1);
}
