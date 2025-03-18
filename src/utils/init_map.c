/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/18 12:13:49 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_del(char **map, int y, int x)
{
	if (y == 6)
		return (1);
	if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1])
		return (1);
	if (!map[y - 1][x] || !map[y + 1][x]
		|| !map[y][x - 1] || !map[y][x + 1])
		return (1);
	if (map[y + 1][x] == ' ' || map[y - 1][x] == ' '
		|| map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
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
	int		max_x;

	max_x = 0;
	if (check_void_lines(cubed->premap))
		return (error(cubed, ERR_MAP_NOT_WALLED));
	map = ft_strtok(cubed->premap, "\n");
	if (check_invalid_chars(map, cubed))
		return (ft_freearr(map), error(cubed, ERR_MAP_INVALID_CHARS));
	if (!map)
		error(cubed, ERR_MAP);
	y = 6;
	if (check_cero(map, &y, &x, &max_x) == 1)
		return (error(cubed, ERR_MAP_NOT_WALLED));
	if (save_map(cubed, map, y, max_x) == 1)
		return (ft_freearr(map), error(cubed, ERR_MALLOC));
	if (cubed->pj_x == 0 && cubed->pj_y == 0)
		return (ft_freearr(map), error(cubed, ERR_PJ_NOT_EXIST));
	return (ft_freearr(map));
}


