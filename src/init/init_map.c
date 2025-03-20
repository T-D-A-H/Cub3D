/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:08:04 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/20 11:53:14 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_cero(char **map, int *y, int *x, int *max_x)
{
	while (map[*y])
	{
		*x = 0;
		while (map[*y][*x])
		{
			if ((map[*y][*x] == '0' || map[*y][*x] == 'N')
				&& is_map_del(map, *y, *x))
				return (ft_freearr(map), 1);
			(*x)++;
		}
		if (*x > *max_x)
			(*max_x) = *x;
		(*y)++;
	}
	return (0);
}

static int	check_invalid_chars(char **map, t_cub *cubed)
{
	int	i;
	int	j;
	int	count;

	i = 5;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_map_char(map[i][j], 0))
			{
				count++;
				cubed->pj_y = i - 6;
				cubed->pj_x = j;
				cubed->start_direction = get_player_direction(map[i][j]);
			}
			else if (is_map_char(map[i][j], 1))
				return (1);
		}
	}
	if (count > 1 || !count)
		return (1);
	return (0);
}

static int	check_void_lines(const char *premap)
{
	char	*ptr;
	int		i;
	int		start;

	i = -1;
	while (premap[++i])
	{
		start = i;
		while (premap[i] && premap[i] != '\n')
			i++;
		ptr = (char *)malloc((i - start) + 1);
		if (!ptr)
			return (1);
		ft_strlcpy(ptr, &premap[start], i - start);
		ptr[i - start] = '\0';
		if (only_one(ptr) && ptr[0] != 0)
		{
			free(ptr);
			break ;
		}
		free(ptr);
	}
	if (check_void(premap, i) == 1)
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
