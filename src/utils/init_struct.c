/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:25:27 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/18 12:16:48 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_struct(t_cub *cubed)
{
	cubed->mlx_ptr = NULL;
	cubed->no_path = NULL;
	cubed->so_path = NULL;
	cubed->we_path = NULL;
	cubed->ea_path = NULL;
	cubed->pj_x = 0;
	cubed->pj_y = 0;
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
	if (ft_strchr(cubed->premap, '\t'))
		cubed->premap = replace_tabs_with_spaces(cubed);
}

char	*replace_tabs_with_spaces(t_cub *cubed)
{
	size_t	i;
	int		j;
	int		tab_count;
	char	*premap_replaced;

	tab_count = ft_strcountchr(cubed->premap, '\t');
	premap_replaced = malloc(ft_strlen(cubed->premap) + (tab_count * 3) + 1);
	if (!premap_replaced)
		error(cubed, ERR_MALLOC);
	i = -1;
	j = 0;
	while (++i < ft_strlen(cubed->premap))
	{
		if (cubed->premap[i] == '\t')
		{
			premap_replaced[j++] = ' ';
			premap_replaced[j++] = ' ';
			premap_replaced[j++] = ' ';
			premap_replaced[j++] = ' ';
		}
		else
			premap_replaced[j++] = cubed->premap[i];
	}
	premap_replaced[j] = '\0';
	return (free(cubed->premap), premap_replaced);
}
