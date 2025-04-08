/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:42:33 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/08 16:53:58 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	door_is_closed(t_cub *cubed, t_player *player)
{
    int	map_x = (int)(player->x / BLOCK);
    int	map_y = (int)(player->y / BLOCK);
    
    // Verificar si hay una puerta cerrada adyacente
    return (cubed->map[map_y + 1][map_x] == 'D' ||
            cubed->map[map_y - 1][map_x] == 'D' ||
            cubed->map[map_y][map_x + 1] == 'D' ||
            cubed->map[map_y][map_x - 1] == 'D');
}

void	update_door(t_cub *cubed, t_game *game)
{
    // Esta función ahora maneja el cierre automático de puertas
    if (game->door_timer > 0)
    {
        game->door_timer--;
        if (game->door_timer == 0 && game->active_door_x != -1)
        {
            // Cerrar la puerta después del tiempo
            cubed->map[game->active_door_y][game->active_door_x] = 'D';
            game->active_door_x = -1;
            game->active_door_y = -1;
        }
    }
}

void	handle_door2(t_cub *cubed, t_player *player, t_game *game)
{
	if (cubed->map[player->my][player->mx + 1] == 'd' && game->sees_door == 0)
	{
		cubed->game->level = 1;
		game->door_xy[0] = player->mx + 1;
		game->door_xy[1] = player->my;
		game->sees_door = 1;
		cubed->map[game->door_xy[1]][game->door_xy[0]] = '1';
	}
	else if (cubed->map[player->my][player->mx - 1] == 'd' && game->sees_door == 0)
	{
		cubed->game->level = 1;
		game->door_xy[0] = player->mx - 1;
		game->door_xy[1] = player->my;
		game->sees_door = 1;
		cubed->map[game->door_xy[1]][game->door_xy[0]] = '1';
	}
}

void	handle_door(t_cub *cubed, t_player *player, t_game *game)
{
    // Manejar puertas abiertas ('d') que el jugador está atravesando
    if (cubed->map[player->my][player->mx] == 'd')
    {
        game->active_door_x = player->mx;
        game->active_door_y = player->my;
        game->door_timer = 60; // 60 frames (2 segundos aprox) antes de cerrar
    }
    
    // Si el jugador presiona F para abrir una puerta
    if (player->key_f)
    {
        player->key_f = false;
        open_door(cubed, player);
    }
}
