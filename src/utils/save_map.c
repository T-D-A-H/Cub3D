/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:31:18 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/18 12:44:10 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	allocate_map(t_cub *cubed, size_t y)
{
	cubed->map = (char **)malloc(sizeof(char *) * (y - 6 + 1));
	if (!cubed->map)
		return (1);
	return (0);
}

static int	allocate_row(t_cub *cubed, char **temp_map, size_t i, size_t x)
{
	size_t	temp_len;
	size_t	j;

	temp_len = ft_strlen(temp_map[i]);
	cubed->map[i - 6] = (char *)malloc((x + 1) * sizeof(char));
	if (!cubed->map[i - 6])
		return (1);
	j = 0;
	while (j < x)
	{
		if (j < temp_len)
			cubed->map[i - 6][j] = temp_map[i][j];
		else
			cubed->map[i - 6][j] = ' ';
		j++;
	}
	cubed->map[i - 6][j] = '\0';
	return (0);
}

int	save_map(t_cub *cubed, char **temp_map, size_t y, size_t x)
{
	size_t	i;

	if (allocate_map(cubed, y))
		return (1);
	i = 6;
	while (i < y)
	{
		if (allocate_row(cubed, temp_map, i, x))
		{
			while (i-- > 6)
				free(cubed->map[i - 6]);
			free(cubed->map);
			return (1);
		}
		i++;
	}
	cubed->map[y - 6] = NULL;
	return (0);
}
