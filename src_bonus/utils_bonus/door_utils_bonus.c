/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:47:09 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/15 14:51:31 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	door_is_open(t_cub *cub, t_player *player)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
	if ((cub->map[map_y + 1][map_x] && cub->map[map_y + 1][map_x] == 'd')
		|| (cub->map[map_y][map_x + 1] && cub->map[map_y][map_x + 1] == 'd')
		|| (cub->map[map_y - 1][map_x] && cub->map[map_y - 1][map_x] == 'd')
		|| (cub->map[map_y][map_x - 1] && cub->map[map_y][map_x - 1] == 'd'))
	{
		return (1);
	}
	return (0);
}

int	door_is_closed(t_cub *cub, t_player *player)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
	if ((cub->map[map_y + 1][map_x] && cub->map[map_y + 1][map_x] == 'D')
		|| (cub->map[map_y][map_x + 1] && cub->map[map_y][map_x + 1] == 'D')
		|| (cub->map[map_y - 1][map_x] && cub->map[map_y - 1][map_x] == 'D')
		|| (cub->map[map_y][map_x - 1] && cub->map[map_y][map_x - 1] == 'D'))
	{
		return (1);
	}
	return (0);
}

static void	set_door(t_cub *cub, int x, int y, int inc_level)
{
	if (cub->game->sees_door)
		return ;
	if (cub->map[y][x] && cub->map[y][x] == 'd')
	{
		cub->game->door_xy[0] = x;
		cub->game->door_xy[1] = y;
		cub->game->sees_door = 1;
		if (inc_level)
			cub->game->level++;
	}
}

void	handle_door(t_cub *cubed, t_player *player, t_game *game)
{
	set_door(cubed, player->mx, player->my + 1, 1);
	set_door(cubed, player->mx, player->my - 1, 0);
	set_door(cubed, player->mx + 1, player->my, 1);
	set_door(cubed, player->mx - 1, player->my, 1);
	if (game->sees_door
		&& (player->my - 2 == game->door_xy[1]
			|| player->mx - 2 == game->door_xy[0]
			|| player->my + 2 == game->door_xy[1]
			|| player->mx + 2 == game->door_xy[0]))
	{
		cubed->map[game->door_xy[1]][game->door_xy[0]] = '1';
		cubed->game->sees_door = 0;
		cubed->game->action_done = 0;
		cubed->game->action_done = 0;
	}
}
