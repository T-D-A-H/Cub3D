/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:25:27 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 13:36:32 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_struct(t_cub *cubed)
{
	cubed->no_path = NULL;
	cubed->so_path = NULL;
	cubed->we_path = NULL;
	cubed->ea_path = NULL;
	cubed->f_color = malloc(sizeof(int) * 3);
	if (!cubed->f_color)
		return (1);
	cubed->c_color = malloc(sizeof(int) * 3);
	if (!cubed->c_color)
		return (1);
	cubed->map = NULL;
	return (0);
}
