/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/13 13:34:23 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cubed;

	if (check_cub_args(argc, argv))
		return (1);
	if (init_struct(&cubed))
		return (1);
	if (init_map_values(&cubed, argv))
		return (1);
	printf("NO = %s\n", cubed.no_path);
	printf("SO = %s\n", cubed.so_path);
	printf("WE = %s\n", cubed.we_path);
	printf("EA = %s\n", cubed.ea_path);
	printf("F = %d,%d,%d\n", cubed.f_color[0], cubed.f_color[1], cubed.f_color[2]);
	printf("C = %d,%d,%d\n", cubed.c_color[0], cubed.c_color[1], cubed.c_color[2]);
	return (0);
}
