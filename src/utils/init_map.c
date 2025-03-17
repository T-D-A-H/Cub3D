/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/17 17:14:04 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_del(char **map, int y, int x)
{
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

int save_map(t_cub *cubed, char **temp_map, size_t y, size_t x)
{
	size_t i;
	size_t j;
	size_t temp_len;

	i = 6;
	cubed->map = (char **)malloc(sizeof(char *) * (y - 6 + 1));
	if (!cubed->map)
		return (1);
	while (i < y)
	{
		j = 0;
		temp_len = ft_strlen(temp_map[i]);
		cubed->map[i - 6] = (char *)malloc((x + 1) * sizeof(char));
		if (!cubed->map[i - 6])
		{
			while (i - 6 > 0)
				free(cubed->map[--i - 6]);
			free(cubed->map);
			return (1);
		}
		while (j < x)
		{
			if (j < temp_len)
				cubed->map[i - 6][j] = temp_map[i][j]; 
			else
				cubed->map[i - 6][j] = ' ';
			j++;
		}
		cubed->map[i - 6][j] = '\0';
		i++;
	}
	cubed->map[i - 6] = NULL;
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
	if (check_invalid_chars(map))
		return (ft_freearr(map), error(cubed, ERR_MAP_INVALID_CHARS));
	if (!map)
		error(cubed, ERR_MAP);
	y = 6;
	if (check_cero(map, &y, &x, &max_x) == 1)
		return (error(cubed, ERR_MAP_NOT_WALLED));
	if (save_map(cubed, map, y, max_x) == 0)
		return (ft_freearr(map));
	return (ft_freearr(map));
}
