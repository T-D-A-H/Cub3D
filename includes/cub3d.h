/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 13:31:07 by ctommasi         ###   ########.fr       */
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

# define ERR_EXTENSION "Error\nExtension doesn't match\n"
# define ERR_ARGS "Error\nWrong amount of arguments\n"
# define ERR_EXTENSION_NOFILENAME "Error\nNo filename\n"
# define ERR_FILE_OPEN "Error\nOpening map file\n"

typedef struct s_cub
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	int *f_color;
	int *c_color;
	char **map;
}	t_cub;

//----------------------------------------------MAIN
int		main(int argc, char **argv);
//----------------------------------------------UTILS
int		check_cub_args(int argc, char **argv);
int		init_struct(t_cub *cubed);
int		init_map_values(t_cub *cubed, char **argv);

#endif