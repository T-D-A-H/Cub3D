/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:29:43 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/25 14:54:22 by ctommasi         ###   ########.fr       */
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

int	is_map_char(char c, int mode)
{
	if (!mode)
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			return (1);
	}
	else
	{
		if (c != '1' && c != '0' && c != '\n' && c != ' ')
			return (1);
	}
	return (0);
}

int	only_one(char *linea)
{
	while (*linea)
	{
		if (*linea != '1' && *linea != ' ')
		{
			return (0);
		}
		linea++;
	}
	return (1);
}

int	check_void(const char *premap, int i)
{
	while (premap[i] && premap[i + 1])
	{
		if (premap[i] == '\n' && premap[i + 1] == '\n')
		{
			if (ft_strchr(&premap[i], '1') || ft_strchr(&premap[i], '0'))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

float	get_player_direction(char c)
{
	if (c == 'N')
		return (PI / 2);
	if (c == 'S')
		return ((3 * PI) / 2);
	if (c == 'W')
		return (PI);
	if (c == 'E')
		return (2 * PI);
	return (0);
}
