/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 19:07:42 by ctommasi         ###   ########.fr       */
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

# define ERR_EXTENSION printf("Error\nExtension doesn't match\n")
# define ERR_ARGS printf("Error\nWrong amount of arguments\n")
# define ERR_EXTENSION_NOFILENAME printf("Error\nNo filename\n")
# define ERR_FILE_OPEN printf("Error\nOpening map file\n")
# define ERR_COLOUR_ALPHA printf("Error\nColours can only contain digits\n")
# define ERR_DUPLICATES printf("Error\nDuplicate variables\n")
# define ERR_MISSING_VARIABLES printf("Error\nMissing variables\n")
# define ERR_MISSING_VALUES printf("Error\nMissing values\n")
# define ERR_COLOUR_LIMITS printf("Error\nColours can only be from 0 - 255\n")

typedef struct s_cub
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		*f_color;
	int		*c_color;
	char	**map;
}	t_cub;

//----------------------------------------------MAIN
int		main(int argc, char **argv);
void	error(t_cub *cubed);
//----------------------------------------------UTILS
int		check_cub_args(int argc, char **argv);
void		init_struct(t_cub *cubed);
int		init_map_variables(t_cub *cubed, char **argv);

#endif