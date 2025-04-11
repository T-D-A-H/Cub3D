/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:18:22 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/11 17:22:42 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	check_cub_args(int argc, char **argv)
{
	int		len;
	char	*ext;

	if (argc != 2)
		return (printf(ERR_ARGS), 1);
	len = ft_strlen(argv[1]);
	ext = ".cub";
	if (len < 5)
		return (printf(ERR_EXTENSION_NOFILENAME), 1);
	if (argv[ft_strlen(argv[1]) - 4] && ft_strcmp(&argv[1][len - 4], ext) != 0)
		return (printf(ERR_EXTENSION), 1);
	if (!argv[1][ft_strlen(argv[1]) - 5]
		|| argv[1][ft_strlen(argv[1]) - 5] == '/')
		return (printf(ERR_EXTENSION_NOFILENAME), 1);
	return (0);
}

int	can_move(t_cub *cubed, double next_x, double next_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(next_x / BLOCK);
	map_y = (int)(next_y / BLOCK);
	if (map_x < 0 || map_y < 0 || map_x >= (int)ft_strlen(cubed->map[0])
		|| map_y >= ft_arrlen(cubed->map))
		return (0);
	if (cubed->map[map_y][map_x] == '1'
		|| cubed->map[map_y][map_x] == 'D' || cubed->map[map_y][map_x] == 'x')
		return (0);
	return (1);
}

void	close_door(t_cub *cubed, t_player *player)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / BLOCK);
	map_y = (int)(player->y / BLOCK);
	if (cubed->map[map_y + 1][map_x] == 'd'
		|| cubed->map[map_y][map_x + 1] == 'd'
		|| cubed->map[map_y - 1][map_x] == 'd'
		|| cubed->map[map_y][map_x - 1] == 'd')
	{
		if (cubed->map[map_y - 1][map_x] == 'd')
			cubed->map[map_y - 1][map_x] = 'D';
		else if (cubed->map[map_y + 1][map_x] == 'd')
			cubed->map[map_y + 1][map_x] = 'D';
		else if (cubed->map[map_y][map_x + 1] == 'd')
			cubed->map[map_y][map_x + 1] = 'D';
		else if (cubed->map[map_y][map_x - 1] == 'd')
			cubed->map[map_y][map_x - 1] = 'D';
		cubed->loop->door_wall = 1;
	}
}

void	open_door(t_cub *cubed, t_player *player)
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
		if (cubed->map[map_y - 1][map_x] == 'D')
			cubed->map[map_y - 1][map_x] = 'd';
		else if (cubed->map[map_y + 1][map_x] == 'D')
			cubed->map[map_y + 1][map_x] = 'd';
		else if (cubed->map[map_y][map_x + 1] == 'D')
			cubed->map[map_y][map_x + 1] = 'd';
		else if (cubed->map[map_y][map_x - 1] == 'D')
			cubed->map[map_y][map_x - 1] = 'd';
		cubed->loop->door_wall = 1;
	}
}
