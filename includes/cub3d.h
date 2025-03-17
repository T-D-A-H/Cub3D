/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/17 11:00:38 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# include "../libft/includes/libft.h"

# define ERR_EXTENSION "Error Extension doesn't match\n"
# define ERR_ARGS "Error Wrong amount of arguments\n"
# define ERR_EXTENSION_NOFILENAME "Error No filename\n"
# define ERR_FILE_OPEN "Error Opening map file\n"
# define ERR_COLOURS "Error Colours can only contain digits (0 - 255)\n"
# define ERR_DUPLICATES "Error Duplicate variables\n"
# define ERR_MISSING_VARIABLES "Error Missing variables\n"
# define ERR_MISSING_VALUES "Error Missing values\n"
# define ERR_MALLOC "Error Malloc\n"
# define ERR_MAP "Error Getting Map\n"
# define ERR_MAP_NOT_WALLED "Error Map not walled\n"
# define NO_ERROR ""

typedef struct s_cub
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		*f_color;
	int		*c_color;
	char	*premap;
	char	**map;
}	t_cub;

//----------------------------------------------MAIN
int		main(int argc, char **argv);
void	error(t_cub *cubed, char *debug_msg);
//----------------------------------------------UTILS
int		check_cub_args(int argc, char **argv);
void	init_struct(t_cub *cubed);
void	read_map_file(t_cub *cubed, char **argv);
void	init_variables(t_cub *cubed);
void	init_map(t_cub *cubed);
//----------------------------------------------DELETE_AFTER
void	print_where_not_walled(char **map, int y, int x);
#endif