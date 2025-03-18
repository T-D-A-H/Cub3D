/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/18 16:20:46 by jaimesan         ###   ########.fr       */
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
# include <stdbool.h>
#include <math.h>

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

# define ERR_EXTENSION "Error\nExtension doesn't match\n"
# define ERR_ARGS "Error\nWrong amount of arguments\n"
# define ERR_EXTENSION_NOFILENAME "Error\nNo filename\n"
# define ERR_FILE_OPEN "Error\nOpening map file\n"
# define ERR_COLOURS "Error\nColours can only contain digits (0 - 255)\n"
# define ERR_DUPLICATES "Error\nDuplicate variables\n"
# define ERR_MISSING_VARIABLES "Error\nMissing variables\n"
# define ERR_MISSING_VALUES "Error\nMissing values\n"
# define ERR_MALLOC "Error\nMalloc\n"
# define ERR_MAP "Error\nGetting Map\n"
# define ERR_MAP_NOT_WALLED "Error\nMap not walled\n"
# define ERR_MAP_INVALID_CHARS "Error\nInvalid chars\n"
# define ERR_MLX_INIT "Error\nInitialising MLX\n"
# define ERR_PJ_NOT_EXIST "Error\nPj does not exit\n"
# define NO_ERROR ""

# define WINDOW_NAME "CUB3D"
# define WINDOW_W 1920
# define WINDOW_H 1080

# define W 119
# define A 97
# define S 115
# define D 100

# define PI 3.141592653589

#define FOV 60 

typedef struct s_player
{
	float	player_x;
	float	player_y;

	float	player_angle;
	float	move_speed;
	float	rotation_speed;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_game;

typedef struct s_cub
{
	void		*mlx_ptr;
	void		*window;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			*f_color;
	int			*c_color;
	char		*premap;
	char		**map;
	int			pj_y;
	int			pj_x;
	char		*textures[4];
	t_game		*game;
	t_player	*player;
}	t_cub;

//----------------------------------------------MAIN
int		main(int argc, char **argv);
void	error(t_cub *cubed, char *debug_msg);
//----------------------------------------------INIT
void	init_struct(t_cub *cubed);
void	read_map_file(t_cub *cubed, char **argv);
void	init_variables(t_cub *cubed);
void	init_map(t_cub *cubed);
void	init_window(t_cub *cubed);
//----------------------------------------------UTILS
int		check_cub_args(int argc, char **argv);
int		is_map_del(char **map, int y, int x);
int		is_map_char(char c, int mode);
int		only_one(char *linea);
int		check_void(const char *premap, int i);
int		save_map(t_cub *cubed, char **temp_map, size_t y, size_t x);
//----------------------------------------------DELETE_AFTER
void	print_where_not_walled(char **map, int y, int x);

#endif