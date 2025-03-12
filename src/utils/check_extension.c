/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:38:17 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/12 18:13:42 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(char *file)
{
	if (!file || !ft_strlen(file))
	{
		printf(ERR_EXTENSION_NOFILENAME);
		return (1);
	}
	if (file[ft_strlen(file) - 4]
		&& ft_strcmp(&file[ft_strlen(file) - 4], ".cub"))
	{
		printf(ERR_EXTENSION);
		return (1);
	}
	if (!file[ft_strlen(file) - 5] || file[ft_strlen(file) - 5] == '/')
	{
		printf(ERR_EXTENSION_NOFILENAME);
		return (1);
	}
	return (0);
}
