/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/18 15:21:11 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void print_map(t_cub *cubed)
{
	for (int i = 0; cubed->map[i]; i++)
		printf("%s\n", cubed->map[i]);
	printf("Eje X del pj: %d\n", cubed->pj_x);
	printf("Eje Y del pj: %d\n", cubed->pj_y);
}

int	main(int argc, char **argv)
{
	t_cub		cubed;
	t_game		game;
	t_player	player;

	cubed.game = &game;
	cubed.player = &player;
	if (check_cub_args(argc, argv))
		return (1);
	init_struct(&cubed);
	read_map_file(&cubed, argv);
	init_variables(&cubed);
	init_map(&cubed);
	init_window(&cubed);
	return (error(&cubed, NO_ERROR), 0);
}
