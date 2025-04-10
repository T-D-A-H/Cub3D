/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:31:18 by jaimesan          #+#    #+#             */
/*   Updated: 2025/04/10 15:31:45 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	allocate_map(t_cub *cubed, size_t y)
{
	cubed->map = (char **)malloc(sizeof(char *) * (y - REST + 1));
	if (!cubed->map)
		return (1);
	return (0);
}

static int	allocate_row(t_cub *cubed, char **temp_map, size_t i, size_t x)
{
	size_t	temp_len;
	size_t	j;

	temp_len = ft_strlen(temp_map[i]);
	cubed->map[i - REST] = (char *)malloc((x + 1) * sizeof(char));
	if (!cubed->map[i - REST])
		return (1);
	j = 0;
	while (j < x)
	{
		if (j < temp_len)
			cubed->map[i - REST][j] = temp_map[i][j];
		else
			cubed->map[i - REST][j] = ' ';
		j++;
	}
	cubed->map[i - REST][j] = '\0';
	return (0);
}

int	save_map(t_cub *cubed, char **temp_map, size_t y, size_t x)
{
	size_t	i;

	if (allocate_map(cubed, y))
		return (1);
	i = REST;
	while (i < y)
	{
		if (allocate_row(cubed, temp_map, i, x))
		{
			while (i-- > REST)
				free(cubed->map[i - REST]);
			free(cubed->map);
			return (1);
		}
		i++;
	}
	cubed->map[y - REST] = NULL;
	return (0);
}

static char	*replace_tabs_with_spaces(t_cub *cubed)
{
	size_t	i;
	int		j;
	int		tab_count;
	char	*premap_replaced;

	tab_count = ft_strcountchr(cubed->premap, '\t');
	premap_replaced = malloc(ft_strlen(cubed->premap) + (tab_count * 3) + 1);
	if (!premap_replaced)
		error(cubed, ERR_MALLOC, 0);
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

void	read_map_file(t_cub *cubed, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error(cubed, ERR_FILE_OPEN, 0);
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
