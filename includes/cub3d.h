/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:24:22 by jaimesan          #+#    #+#             */
/*   Updated: 2025/03/13 12:17:42 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/includes/libft.h"

# define ERROR_EXTENSION printf("Error: The file must have a .cub extension\n")
# define ERROR_FILES printf("Error: ./cub3D  <file.cub>\n")

typedef struct s_cub
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	int f_color[3];
	int c_color[3];
	char **map;
}	t_cub;

// Main
int main(int argc, char **argv);

// Utils
int	check_cub_args(int argc, char **argv);

#endif