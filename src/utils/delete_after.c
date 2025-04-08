/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:01:38 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/08 13:07:34 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_where_not_walled(char **map, int y, int x)
{
	int		i;
	int		j;

	i = REST;
	while (map[i])
	{
		if (i != y)
			printf("\033[1;32m%s\033[0m\n", map[i]);
		else
		{
			j = 0;
			while (map[i][j])
			{
				if (j != x)
					printf("\033[1;32m%c\033[0m", map[i][j]);
				else
					printf("\033[1;31m%c\033[0m", map[i][j]);
				j++;
			}
			printf("\n");
		}
		i++;
	}
}
