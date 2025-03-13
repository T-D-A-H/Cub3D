/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:18:22 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/13 11:25:18 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cub_args(int argc, char **argv)
{
	int		len;
	char	*ext;

	if (argc != 2)
		return (ERROR_FILES, -1);
	len = ft_strlen(argv[1]);
	ext = ".cub";
	if (len < 5 || ft_strcmp(&argv[1][len - 4], ext) != 0
		|| argv[1][len - 5] == '/')
		return (ERROR_EXTENSION, -1);
	return (0);
}
