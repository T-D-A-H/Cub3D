/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:45:06 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/11 17:45:09 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub		cubed;
	t_game		game;
	t_player	player;
	t_loop		loop;

	cubed.game = &game;
	cubed.player = &player;
	cubed.loop = &loop;
	if (check_cub_args(argc, argv))
		return (1);
	init_struct(&cubed);
	read_map_file(&cubed, argv);
	init_variables(&cubed);
	init_map(&cubed);
	init_window(&cubed);
	return (error(&cubed, NO_ERROR, 1), 0);
}
