/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:42:33 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/07 14:55:51 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	door_is_closed(t_cub *cubed, t_player *player)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
	if (cubed->map[map_y + 1][map_x] == 'D'
		|| cubed->map[map_y][map_x + 1] == 'D'
		|| cubed->map[map_y - 1][map_x] == 'D'
		|| cubed->map[map_y][map_x - 1] == 'D')
	{
		return (1);
	}
	return (0);
}

void	update_door(t_cub *cubed, t_player *player, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
	if (cubed->map[map_y][map_x] == 'd' && game->sees_door == 0)
	{
		game->door_xy[0] = map_x;
		game->door_xy[1] = map_y;
		game->sees_door = 1;
	}
	if (game->sees_door == 1
		&& (map_y - 1 == game->door_xy[1] || map_x - 1 == game->door_xy[0]
			|| map_y + 1 == game->door_xy[1] || map_x + 1 == game->door_xy[0]))
	{
		cubed->map[game->door_xy[1]][game->door_xy[0]] = '1';
		cubed->game->sees_door = 0;
		cubed->game->level++;
	}
}
