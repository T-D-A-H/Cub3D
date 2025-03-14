/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/13 19:07:03 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_del(char **map, int y, int x)
{
	if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1])
		return (1);
	if (!map[y - 1] || !map[y - 1][x] || !map[y + 1] || !map[y + 1][x])
		return (1);
	if (!map[y][x - 1] || !map[y][x + 1])
		return (1);
	if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
		return (1);
	if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
		return (1);
	if (map[y + 1][x] == '\n' || map[y][x + 1] == '\n')
		return (1);
	return (0);
}

void	init_map(t_cub *cubed)
{
	char	**map;
	int		y;
	int		x;

	map = ft_strtok(cubed->premap, "\n");
	if (!map)
		error(cubed, ERR_MAP);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' && is_map_del(map, y, x))
			{
				printf(ERR_MAP_NOT_WALLED);
				//print_where_not_walled(map, y, x);
				error(cubed, "!");
			}
			x++;
		}
		y++;
	}
}
