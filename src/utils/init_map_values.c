/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:30:25 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 13:36:22 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_colour_values(t_cub *cubed, char **premap)
{
	int		i;

	i = 0;
	while (i < ft_arrlen(premap))
	{
		if (premap[i] && premap[i + 1] && premap[i + 2] && premap[i + 3])
		{
			if (!ft_strncmp(premap[i], "F", 2))
			{
				cubed->f_color[0] = ft_atoi(premap[i + 1]);
				cubed->f_color[1] = ft_atoi(premap[i + 2]);
				cubed->f_color[2] = ft_atoi(premap[i + 3]);
			}
			if (!ft_strncmp(premap[i], "C", 2))
			{
				cubed->f_color[0] = ft_atoi(premap[i + 1]);
				cubed->f_color[1] = ft_atoi(premap[i + 2]);
				cubed->f_color[2] = ft_atoi(premap[i + 3]);
			}
		}
		i++;
	}
	return (0);
}

static int	init_texture_files(t_cub *cubed, char **premap)
{
	int		i;

	i = 0;
	while (i < ft_arrlen(premap))
	{
		if (!ft_strncmp(premap[i], "NO", 2) && premap[i + 1])
			cubed->no_path = ft_strdup(premap[i + 1]);
		else if (!ft_strncmp(premap[i], "SO", 2) && premap[i + 1])
			cubed->so_path = ft_strdup(premap[i + 1]);
		else if (!ft_strncmp(premap[i], "WE", 2) && premap[i + 1])
			cubed->we_path = ft_strdup(premap[i + 1]);
		else if (!ft_strncmp(premap[i], "EA", 2) && premap[i + 1])
			cubed->ea_path = ft_strdup(premap[i + 1]);
		i++;
	}
	return (0);
}

int	init_map_values(t_cub *cubed, char **argv)
{
	char	**premap;
	char	*line;
	char	*temp;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf(ERR_FILE_OPEN), 1);
	temp = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoinf(temp, line);
		free(line);
	}
	premap = ft_strtok(temp, "\n ,");
	if (!premap)
		return (free(temp), 1);
	if (init_texture_files(cubed, premap))
		return (ft_freearr(premap), free(temp), 1);
	if (init_colour_values(cubed, premap))
		return (ft_freearr(premap), free(temp), 1);
	return (ft_freearr(premap), free(temp), 0);
}
