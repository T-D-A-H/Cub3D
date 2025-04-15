/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:30:25 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 19:08:26 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_bonus_keys(t_cub *cubed, char **map)
{
	int					i;
	static const char	*keys[] = {
		"KY", "WDO", "WD", "FL", "CE", "WA",
		"WDO1", "WD1", "FL1", "CE1", "WA1",
		"WDO2", "WD2", "FL2", "CE2", "WA2",
		"WDO3", "WD3", "FL3", "CE3", "WA3",
		NULL
	};

	i = -1;
	while (keys[++i])
		check_dupe_or_missing(cubed, keys[i], map, 0);
}

int	get_bonus_tex_index(char *key)
{
	int					i;
	static const char	*keys[] = {
		"KY", "WDO", "WD", "FL", "CE", "WA",
		"WDO1", "WD1", "FL1", "CE1", "WA1",
		"WDO2", "WD2", "FL2", "CE2", "WA2",
		"WDO3", "WD3", "FL3", "CE3", "WA3",
		NULL
	};

	i = 0;
	while (keys[i])
	{
		if (!ft_strcmp(keys[i], key))
			return (i);
		i++;
	}
	return (-1);
}

int	contains_alpha(char *s1, char *s2, char *s3)
{
	int		i;

	if (ft_atoi(s1) < 0 || ft_atoi(s2) < 0 || ft_atoi(s3) < 0
		|| ft_atoi(s1) > 255 || ft_atoi(s2) > 255 || ft_atoi(s3) > 255)
		return (1);
	i = -1;
	while (s1[++i])
	{
		if (!ft_isdigit(s1[i]))
			return (1);
	}
	i = -1;
	while (s2[++i])
	{
		if (!ft_isdigit(s2[i]))
			return (1);
	}
	i = -1;
	while (s3[++i])
	{
		if (!ft_isdigit(s3[i]))
			return (1);
	}
	return (0);
}

void	check_dupe_or_missing(t_cub *cubed, const char *del,
	char **map, int mode)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (map[i])
	{
		if (!ft_strcmp(map[i], del))
		{
			n++;
			if (!mode && n == 1 && !map[i + 1])
				return (ft_freearr(map), error(cubed, ERR_MISSING_VALUES, 0));
			if (mode && n == 1 && (!map[i + 1] || !map[i + 2] || !map[i + 3]))
				return (ft_freearr(map), error(cubed, ERR_MISSING_VALUES, 0));
			if (mode && contains_alpha(map[i + 1], map[i + 2], map[i + 3]))
				return (ft_freearr(map), error(cubed, ERR_COLOURS, 0));
			if (n > 1)
				return (ft_freearr(map), error(cubed, ERR_DUPLICATES, 0));
		}
		i++;
	}
	if (!n)
		return (ft_freearr(map), error(cubed, ERR_MISSING_VARIABLES, 0));
}

void	init_variables(t_cub *cubed)
{
	char	**map;
	int		i;
	int		index;

	map = ft_strtok(cubed->premap, "\n ,");
	cubed->tex_paths[0] = NULL;
	if (!map)
		error(cubed, ERR_MAP, 0);
	check_bonus_keys(cubed, map);
	i = 0;
	while (map[i] && map[i + 1])
	{
		index = get_bonus_tex_index(map[i]);
		if (index != -1 && map[i + 1])
		{
			cubed->tex_paths[index] = ft_strdup(map[i + 1]);
			if (!cubed->tex_paths[index])
				error(cubed, ERR_MEMORY_TEXTURE, 0);
			i++;
		}
		i++;
	}
	ft_freearr(map);
}
