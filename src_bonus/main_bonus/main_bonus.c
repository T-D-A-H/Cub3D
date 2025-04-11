/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:56:25 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/11 16:56:32 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_cub		cubed;
	t_game		game;
	t_player	player;
	t_loop		loop;
	t_sounds	sounds;

	cubed.game = &game;
	cubed.player = &player;
	cubed.loop = &loop;
	cubed.sounds = &sounds;
	if (check_cub_args(argc, argv))
		return (1);
	init_struct(&cubed);
	read_map_file(&cubed, argv);
	init_variables(&cubed);
	init_map(&cubed);
	init_game(&cubed);
	return (error(&cubed, NO_ERROR, 1), 0);
}
