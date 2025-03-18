/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:55:30 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/18 11:36:16 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	check_void_lines(const char *premap)
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

int	check_invalid_chars(char **map, t_cub *cubed)
{
	int	i;
	int	j;

	i = 6;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				cubed->pj_y = i -6;
				cubed->pj_x = j;
			}
			else if (map[i][j] != '1' && map[i][j] != '0'
			&& map[i][j] != '\n' && map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_cero(char **map, int *y, int *x, int *max_x)
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
