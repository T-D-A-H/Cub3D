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
		check_bonus_keys(cubed, map);
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
