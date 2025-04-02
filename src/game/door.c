/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:22:19 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/02 12:58:32 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void handle_door_interaction(t_cub *cubed, t_player *player)
{
    int map_x;
    int map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
    if (cubed->map[map_y + 1][map_x] == 'D' 
		|| cubed->map[map_y][map_x + 1] == 'D' 
		|| cubed->map[map_y - 1][map_x] == 'D'
		|| cubed->map[map_y][map_x - 1] == 'D'
		|| cubed->map[map_y + 1][map_x] == 'd'
		|| cubed->map[map_y][map_x + 1] == 'd'
		|| cubed->map[map_y - 1][map_x] == 'd'
		|| cubed->map[map_y][map_x - 1] == 'd')
	{
		if ( cubed->map[map_y - 1][map_x] == 'D')
			cubed->map[map_y - 1][map_x] = 'd';
		else if (cubed->map[map_y + 1][map_x] == 'D')
			cubed->map[map_y + 1][map_x]  = 'd';
		else if (cubed->map[map_y][map_x + 1] == 'D')
			cubed->map[map_y][map_x + 1] = 'd';
		else if (cubed->map[map_y][map_x - 1] == 'D')
			cubed->map[map_y][map_x - 1] = 'd';
		else if (cubed->map[map_y - 1][map_x] == 'd')
			cubed->map[map_y - 1][map_x] = 'D';
		else if (cubed->map[map_y + 1][map_x] == 'd')
			cubed->map[map_y + 1][map_x] = 'D';
		else if (cubed->map[map_y][map_x + 1] == 'd')
			cubed->map[map_y][map_x + 1] = 'D';
		else if (cubed->map[map_y][map_x - 1] == 'd')
			cubed->map[map_y][map_x - 1] = 'D';
    }
}