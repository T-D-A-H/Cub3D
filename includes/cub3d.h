/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/04/15 12:48:13 by jaimesan         ###   ########.fr       */
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
# include <math.h>

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

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
# define ERR_PJ_NOT_EXIST "Error\nPlayer does not exist\n"
# define ERR_LOAD_TEXTUE "Error\nLoading texture\n"
# define ERR_MEMORY_TEXTUE "Error\nMemory allocation failed for texture path.\n"
# define NO_ERROR ""

# define W_NAME "CUB3D"
# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64
# define MAP 16
# define MAX_OBJECTS 20
# define MAX_TEXTURES 4
# define REST 6

# define PLAYER_SIZE 32
# define MOVE_AMOUNT 3
# define MOVE_SPEED 0.02
# define PI 3.1415926535

# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define BLUE 0x1414b8
# define PURPLE 0xA400A4
# define GREY 0x8a9597
# define RED 0xFF0000
# define WHITE 0xFFFFFF

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307

typedef struct draw
{
	int		visible_samples;
	int		total_samples;
	double	block_y;
	double	block_x;
	double	tx;
	double	ty;
	int		visible;
}	t_object_porc;

typedef struct s_loop
{
	double	fov;
	double	ray_angle;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	int		map_x;
	int		map_y;
	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perpwalldist;
	int		line_height;
	int		drawstart;
	int		drawend;
	int		texx;
	int		x;
}	t_loop;

typedef struct s_draw
{
	int		color;
	int		texi;
	double	wallx;
	double	step;
	double	texpos;
	int		texy;
}	t_draw;

typedef struct s_player
{
	double	x;
	double	y;
	int		mx;
	int		my;
	double	dx;
	double	dy;
	double	angle;
	bool	key_w;
	bool	key_s;
	bool	key_a;
	bool	key_d;
	bool	key_left;
	bool	key_right;
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

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	double	sidedist_xy[2];
	double	perpwalldist;
	int		line_height;
	int		drawstart;
	int		drawend;
	int		color;
	int		tex_id;
	double	wallx;
	double	step;
	double	texpos;
	int		texx;
	int		texy;
	int		side;
}	t_texture;

typedef struct s_cub
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f_color;
	int			c_color;
	char		*premap;
	char		**map;
	int			pj_y;
	int			pj_x;
	float		start_direction;
	t_texture	*textures[MAX_TEXTURES];
	t_game		*game;
	t_player	*player;
	t_loop		*loop;
	char		*tex_paths[MAX_TEXTURES];
}	t_cub;

//------------------------------------------------------------MAIN
int		main(int argc, char **argv);
void	error(t_cub *cubed, char *debug_msg, int signal);
//--------------------------------------------------------INIT-variables
void	init_variables(t_cub *cubed);
void	check_dupe_or_missing(t_cub *cubed, const char *del, char **map,
			int mode);
int		contains_alpha(char *s1, char *s2, char *s3);
void	init_variable_values(t_cub *cubed, char **map, int i);
//--------------------------------------------------------INIT-map
int		check_cero(char **map, int *y, int *x, int *max_x);
int		check_invalid_chars(char **map, t_cub *cubed);
int		check_void_lines(const char *premap);
void	init_map(t_cub *cubed);
//-----------------------------------------------------------INIT-game
void	init_window(t_cub *cubed);
void	init_game(t_game *game, t_cub *cubed);
int		game_loop(void *param);
void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed);
void	init_struct(t_cub *cubed);
//------------------------------------------------------------GAME-textures
void	load_all_textures(t_cub *cub);
void	load_texture(t_cub *cub, char *path, int index);
//------------------------------------------------------GAME-raycasting
void	raycasting(t_cub *cubed, t_player *player, t_loop *loop);
void	get_raycast_hits(t_cub *cubed, t_loop *loop);
void	get_raycast_steps(t_player *player, t_loop *loop);
void	init_loop(t_loop *loop);
void	init_ray(t_player *player, t_loop *loop, int x);
//--------------------------------------------------GAME-draw_map
void	get_wall_textures(t_cub *cub, t_loop *loop, t_draw *draw);
void	init_start_end(t_loop *loop);
void	get_coor_textures(t_cub *cub, t_loop *loop, t_draw *draw);
//-----------------------------------------------------------GAME-draw
void	put_pixel(int x, int y, int colour, t_cub *cubed);
void	clear_screen(t_cub *cubed);
void	draw_3dmap(t_cub *cubed, int draw_start, int draw_end, int x);
void	draw_walls(t_cub *cub, t_loop *loop, t_draw *draw, int x);
//--------------------------------------------------------GAME-move_player
int		can_move(t_cub *cubed, double next_x, double next_y);
void	rotate_player(t_player *player);
int		move_player(t_player *player, t_cub *cub);
void	key_player(t_player *player, double *next_x, double *next_y);
void	strafe_player(t_player *player, t_cub *cubed);
//-----------------------------------------------------------GAME-keypress
int		on_keypress(int keydata, t_cub *cub);
int		on_keyrelease(int keydata, t_player *player);
//-------------------------------------------------------------------------UTILS
void	read_map_file(t_cub *cubed, char **argv);
int		check_cub_args(int argc, char **argv);
int		is_map_del(char **map, int y, int x);
int		is_map_char(char c, int mode);
int		only_one(char *linea);
int		check_void(const char *premap, int i);
int		save_map(t_cub *cubed, char **temp_map, size_t y, size_t x);
float	get_player_direction(char c);
int		close_window(t_cub *cubed);

#endif