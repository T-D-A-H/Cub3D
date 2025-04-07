/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/07 14:07:55 by jaimesan         ###   ########.fr       */
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
	return (error(&cubed, NO_ERROR), 0);
}
