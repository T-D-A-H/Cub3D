/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:30:25 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 19:08:26 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	contains_alpha(char *s1, char *s2, char *s3)
{
	int		i;
	int		nb1;
	int		nb2;
	int		nb3;

	nb1 = ft_atoi(s1);
	nb2 = ft_atoi(s2);
	nb3 = ft_atoi(s3);
	i = 0;
	if (nb1 < 0 || nb1 < 0 || nb2 < 0 || nb2 > 255 || nb3 > 255 || nb3 > 255)
		return (ERR_COLOUR_LIMITS, 1);
	while (i < 3)
	{
		if ((s1[i] && s1[i] != '\0' && !ft_isdigit(s1[i]))
			|| (s2[i] && s2[i] != '\0' && !ft_isdigit(s2[i]))
			|| (s3[i] && s3[i] != '\0' && !ft_isdigit(s3[i])))
			return (ERR_COLOUR_ALPHA, 1);
		i++;
	}
	return (0);
}

static void	init_variable_values(t_cub *cubed, char **map, int i)
{
	while (i < ft_arrlen(map))
	{
		if (!ft_strcmp(map[i], "F") && map[i + 1] && map[i + 2] && map[i + 3])
		{
			cubed->f_color[0] = ft_atoi(map[i + 1]);
			cubed->f_color[1] = ft_atoi(map[i + 2]);
			cubed->f_color[2] = ft_atoi(map[i + 3]);
		}
		else if (!ft_strcmp(map[i], "C") && map[i + 1] && map[i + 2] && map[i + 3])
		{
			cubed->c_color[0] = ft_atoi(map[i + 1]);
			cubed->c_color[1] = ft_atoi(map[i + 2]);
			cubed->c_color[2] = ft_atoi(map[i + 3]);
		}
		else if (!ft_strcmp(map[i], "NO") && map[i + 1])
			cubed->no_path = ft_strdup(map[i + 1]);
		else if (!ft_strcmp(map[i], "SO") && map[i + 1])
			cubed->so_path = ft_strdup(map[i + 1]);
		else if (!ft_strcmp(map[i], "WE") && map[i + 1])
			cubed->we_path = ft_strdup(map[i + 1]);
		else if (!ft_strcmp(map[i], "EA") && map[i + 1])
			cubed->ea_path = ft_strdup(map[i + 1]);
		i++;
	}
}

static int	check_dupe_or_missing(char *delimeter, char **map, int mode)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (map[i])
	{
		if (!ft_strcmp(map[i], delimeter))
		{
			n++;
			if (!mode && n == 1 && !map[i + 1])
				return (ERR_MISSING_VALUES, 1);
			if (mode && n == 1 && (!map[i + 1] || !map[i + 2] || !map[i + 3]))
				return (ERR_MISSING_VALUES, 1);
			if (mode && contains_alpha(map[i + 1], map[i + 2], map[i + 3]))
				return (1);
			if (n > 1)
				return (ERR_DUPLICATES, 1);
		}
		i++;
	}
	if (!n)
		return (ERR_MISSING_VARIABLES, 1);
	return (0);
}

static int	init_map_variables_check(t_cub *cubed, char **map)
{
	if (check_dupe_or_missing("NO", map, 0))
		return (1);
	if (check_dupe_or_missing("SO", map, 0))
		return (1);
	if (check_dupe_or_missing("WE", map, 0))
		return (1);
	if (check_dupe_or_missing("EA", map, 0))
		return (1);
	if (check_dupe_or_missing("F", map, 1))
		return (1);
	if (check_dupe_or_missing("C", map, 1))
		return (1);
	cubed->f_color = malloc(sizeof(int) * 3);
	if (!cubed->f_color)
		return (1);
	cubed->c_color = malloc(sizeof(int) * 3);
	if (!cubed->c_color)
		return (1);
	init_variable_values(cubed, map, 0);
	return (0);
}

int	init_map_variables(t_cub *cubed, char **argv)
{
	char	**map;
	char	*line;
	char	*temp;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ERR_FILE_OPEN, 1);
	temp = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoinf(temp, line);
		free(line);
	}
	free(line);
	map = ft_strtok(temp, "\n\r\t ,");
	if (!map)
		return (free(temp), close(fd), 1);
	if (init_map_variables_check(cubed, map))
		return (ft_freearr(map), free(temp), close(fd), 1);
	return (ft_freearr(map), free(temp), close(fd), 0);
}
