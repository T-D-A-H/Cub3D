/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:25:27 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 13:36:32 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_struct(t_cub *cubed)
{
	cubed->no_path = NULL;
	cubed->so_path = NULL;
	cubed->we_path = NULL;
	cubed->ea_path = NULL;
	cubed->map = NULL;
	cubed->premap = NULL;
	cubed->f_color = malloc(sizeof(int) * 3);
	if (!cubed->f_color)
		error(cubed, ERR_MALLOC);
	cubed->c_color = malloc(sizeof(int) * 3);
	if (!cubed->c_color)
		error(cubed, ERR_MALLOC);
}

void	read_map_file(t_cub *cubed, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error(cubed, ERR_FILE_OPEN);
	cubed->premap = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		cubed->premap = ft_strjoinf(cubed->premap, line);
		free(line);
	}
	close(fd);
}
