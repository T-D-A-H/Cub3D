/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:42:33 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/08 17:17:40 by jaimesan         ###   ########.fr       */
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

void	handle_door(t_cub *cubed, t_player *player, t_game *game)
{
	if (cubed->map[player->my + 1][player->mx] == 'd' && game->sees_door == 0)
	{
		cubed->game->level++;
		game->door_xy[0] = player->mx;
		game->door_xy[1] = player->my + 1;
		game->sees_door = 1;
	}
	else if (cubed->map[player->my - 1][player->mx] == 'd' && game->sees_door == 0)
	{
		game->door_xy[0] = player->mx;
		game->door_xy[1] = player->my - 1;
		game->sees_door = 1;
	}
	else if (cubed->map[player->my][player->mx + 1] == 'd' && game->sees_door == 0)
	{
		cubed->game->level++;
		game->door_xy[0] = player->mx + 1;
		game->door_xy[1] = player->my;
		game->sees_door = 1;
	}
	else if (cubed->map[player->my][player->mx - 1] == 'd' && game->sees_door == 0)
	{
		cubed->game->level++;
		game->door_xy[0] = player->mx - 1;
		game->door_xy[1] = player->my;
		game->sees_door = 1;
	}
	if (game->sees_door == 1
		&& (player->my - 2 == game->door_xy[1] || player->mx - 2 == game->door_xy[0]
			|| player->my + 2 == game->door_xy[1] || player->mx + 2 == game->door_xy[0]))
	{
		cubed->map[game->door_xy[1]][game->door_xy[0]] = '1';
		cubed->game->sees_door = 0;
	}
}
