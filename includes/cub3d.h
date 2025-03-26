/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/26 17:02:19 by jaimesan         ###   ########.fr       */
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
# define NO_ERROR ""

# define W_NAME "CUB3D"
# define WIDTH 2048
# define HEIGHT 1024
# define BLOCK 64

# define PLAYER_SIZE 32
# define MOVE_AMOUNT 5
# define MOVE_SPEED 0.03
# define PI 3.1415926535

# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define PURPLE 0xA400A4

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

typedef struct s_loop
{
	double	fov;
	double	ray_angle;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texX;
}	t_loop;


typedef struct s_player
{
	double	x;
	double	y;
	int		mx;
	int		my;
	double	dx;
	double	dy;
	double	angle;

	bool key_w;
	bool key_s;
	bool key_a;
	bool key_d;
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

typedef struct s_texture
{
    void    *img;
    int		*data;
    int     width;
    int     height;
	int		bpp;
	int		size_line;
	int		endian;
} t_texture;

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
	t_texture		*textures[4];
	t_game		*game;
	t_player	*player;
	t_loop		*loop;
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
void	init_loop(t_loop *loop);
void	init_player(t_player *player, int s_x, int s_y, t_cub *cubed);
void	init_game(t_game *game, t_cub *cubed);
//----------------------------------------------GAME-game_loop
int		game_loop(void *param);
void	raycasting(t_cub *cubed, t_player *player, t_loop *loop);
void	get_raycast_hits(t_cub *cubed, t_loop *loop);
void	get_raycast_steps(t_player *player, t_loop *loop);
//----------------------------------------------GAME-draw
void	put_pixel(int x, int y, int colour, t_cub *cubed);
void 	clear_screen(t_cub *cubed);
void	draw_3dmap(t_cub *cubed, int draw_start, int draw_end, int x, int side);
//----------------------------------------------GAME-keypress
void	rotate_player(t_player *player);
void	strafe_player(t_player *player);
int		on_keypress(int keydata, t_player *player);
int		on_keyrelease(int keydata, t_player *player);
int		move_player(t_player *player);
//----------------------------------------------GAME-minimap
void 	draw_map(t_cub *cubed);
void 	draw_full_square(t_cub *cubed, int x, int y, int colour);
void 	draw_empty_square(int x, int y, int size, int color, t_cub *cubed);
void	draw_rays(t_cub *cubed, int x0, int y0, int x1, int y1, int color);
//----------------------------------------------UTILS
int		check_cub_args(int argc, char **argv);
int		is_map_del(char **map, int y, int x);
int		is_map_char(char c, int mode);
int		only_one(char *linea);
int		check_void(const char *premap, int i);
int		save_map(t_cub *cubed, char **temp_map, size_t y, size_t x);
float	get_player_direction(char c);
//----------------------------------------------DELETE_AFTER
void	print_where_not_walled(char **map, int y, int x);

#endif