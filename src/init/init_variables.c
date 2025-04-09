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

#include "../../includes/cub3d.h"

void	init_variable_values(t_cub *cubed, char **map, int i)
{
	while (++i < ft_arrlen(map))
	{
		if (!ft_strcmp(map[i], "F"))
		{
			cubed->f_color += ft_atoi(map[i + 1]) << 16;
			cubed->f_color += ft_atoi(map[i + 2]) << 8;
			cubed->f_color += ft_atoi(map[i + 3]);
		}
		else if (!ft_strcmp(map[i], "C"))
		{
			cubed->c_color += ft_atoi(map[i + 1]) << 16;
			cubed->c_color += ft_atoi(map[i + 2]) << 8;
			cubed->c_color += ft_atoi(map[i + 3]);
		}
		else if (!ft_strcmp(map[i], "NO"))
			cubed->no_path = ft_strdup(map[i + 1]);
		else if (!ft_strcmp(map[i], "SO"))
			cubed->so_path = ft_strdup(map[i + 1]);
		else if (!ft_strcmp(map[i], "WE"))
			cubed->we_path = ft_strdup(map[i + 1]);
		else if (!ft_strcmp(map[i], "EA"))
			cubed->ea_path = ft_strdup(map[i + 1]);
	}
}

int	get_bonus_tex_index(char *key)
{
	if (!ft_strcmp(key, "KY"))
		return (0);
	if (!ft_strcmp(key, "WDO"))
		return (1);
	if (!ft_strcmp(key, "WD"))
		return (2);
	if (!ft_strcmp(key, "FL"))
		return (3);
	if (!ft_strcmp(key, "CE"))
		return (4);
	if (!ft_strcmp(key, "WA"))
		return (5);
	if (!ft_strcmp(key, "WDO1"))
		return (6);
	if (!ft_strcmp(key, "WD1"))
		return (7);
	if (!ft_strcmp(key, "FL1"))
		return (8);
	if (!ft_strcmp(key, "CE1"))
		return (9);
	if (!ft_strcmp(key, "WA1"))
		return (10);
	if (!ft_strcmp(key, "WDO2"))
		return (11);
	if (!ft_strcmp(key, "WD2"))
		return (12);
	if (!ft_strcmp(key, "FL2"))
		return (13);
	if (!ft_strcmp(key, "CE2"))
		return (14);
	if (!ft_strcmp(key, "WA2"))
		return (15);
	if (!ft_strcmp(key, "WDO3"))
		return (16);
	if (!ft_strcmp(key, "WD3"))
		return (17);
	if (!ft_strcmp(key, "FL3"))
		return (18);
	if (!ft_strcmp(key, "CE3"))
		return (19);
	if (!ft_strcmp(key, "WA3"))
		return (20);
	return (-1);
}

void	init_bonus_textures(t_cub *cubed, char **map)
{
	int	i;
	int	index;

	i = 0;
	while (map[i] && map[i + 1])
	{
		index = get_bonus_tex_index(map[i]);
		if (index != -1 && map[i + 1])
		{
			cubed->tex_paths[index] = ft_strdup(map[i + 1]);
			if (!cubed->tex_paths[index])
				error(cubed, "Error\nMemory allocation failed for texture path.\n");
			i++;
		}
		i++;
	}
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

void	check_dupe_or_missing(t_cub *cubed, char *del, char **map, int mode)
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
				return (ft_freearr(map), error(cubed, ERR_MISSING_VALUES));
			if (mode && n == 1 && (!map[i + 1] || !map[i + 2] || !map[i + 3]))
				return (ft_freearr(map), error(cubed, ERR_MISSING_VALUES));
			if (mode && contains_alpha(map[i + 1], map[i + 2], map[i + 3]))
				return (ft_freearr(map), error(cubed, ERR_COLOURS));
			if (n > 1)
				return (ft_freearr(map), error(cubed, ERR_DUPLICATES));
		}
		i++;
	}
	if (!n)
		return (ft_freearr(map), error(cubed, ERR_MISSING_VARIABLES));
}

void	init_variables(t_cub *cubed)
{
	char	**map;

	map = ft_strtok(cubed->premap, "\n ,");
	if (!map)
		error(cubed, ERR_MAP);
	if (BONUS)
	{
		check_dupe_or_missing(cubed, "KY", map, 0);
		check_dupe_or_missing(cubed, "WDO", map, 0);
		check_dupe_or_missing(cubed, "WD", map, 0);
		check_dupe_or_missing(cubed, "FL", map, 0);
		check_dupe_or_missing(cubed, "CE", map, 0);
		check_dupe_or_missing(cubed, "WA", map, 0);
		check_dupe_or_missing(cubed, "WDO1", map, 0);
		check_dupe_or_missing(cubed, "WD1", map, 0);
		check_dupe_or_missing(cubed, "FL1", map, 0);
		check_dupe_or_missing(cubed, "CE1", map, 0);
		check_dupe_or_missing(cubed, "WA1", map, 0);
		check_dupe_or_missing(cubed, "WDO2", map, 0);
		check_dupe_or_missing(cubed, "WD2", map, 0);
		check_dupe_or_missing(cubed, "FL2", map, 0);
		check_dupe_or_missing(cubed, "CE2", map, 0);
		check_dupe_or_missing(cubed, "WA2", map, 0);
		check_dupe_or_missing(cubed, "WDO3", map, 0);
		check_dupe_or_missing(cubed, "WD3", map, 0);
		check_dupe_or_missing(cubed, "FL3", map, 0);
		check_dupe_or_missing(cubed, "CE3", map, 0);
		check_dupe_or_missing(cubed, "WA3", map, 0);
		init_bonus_textures(cubed, map);
	}
	else
	{
		check_dupe_or_missing(cubed, "NO", map, 0);
		check_dupe_or_missing(cubed, "SO", map, 0);
		check_dupe_or_missing(cubed, "WE", map, 0);
		check_dupe_or_missing(cubed, "EA", map, 0);
		check_dupe_or_missing(cubed, "F", map, 1);
		check_dupe_or_missing(cubed, "C", map, 1);
		init_variable_values(cubed, map, -1);
	}
	ft_freearr(map);
}
