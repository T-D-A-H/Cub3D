/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:10:28 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/10 13:16:36 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
				error(cubed, ERR_MEMORY_TEXTUE, 0);
			i++;
		}
		i++;
	}
}
