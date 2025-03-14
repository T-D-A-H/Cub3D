/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:18:22 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/13 12:16:02 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cub_args(int argc, char **argv)
{
	int		len;
	char	*ext;

	if (argc != 2)
		return (printf(ERR_ARGS), 1);
	len = ft_strlen(argv[1]);
	ext = ".cub";
	if (len < 5)
	{
		printf(ERR_EXTENSION_NOFILENAME);
		return (1);
	}
	if (argv[ft_strlen(argv[1]) - 4] && ft_strcmp(&argv[1][len - 4], ext) != 0)
	{
		printf(ERR_EXTENSION);
		return (1);
	}
	if (!argv[1][ft_strlen(argv[1]) - 5]
		|| argv[1][ft_strlen(argv[1]) - 5] == '/')
	{
		printf(ERR_EXTENSION_NOFILENAME);
		return (1);
	}
	return (0);
}
