/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:18:22 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/12 15:26:46 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cub_args(int argc, char **argv)
{
	int		len;
	char	*ext;

	if (argc != 2)
		return (printf("Error: ./cub3D  <file.cub>\n"), -1);
	len = ft_strlen(argv[1]);
	ext = ".cub";
	if (len < 5 || ft_strcmp(&argv[1][len - 4], ext) != 0
		|| argv[1][len - 5] == '/')
		return (printf("Error: The file must have a .cub extension\n"), -1);
	return (0);
}
