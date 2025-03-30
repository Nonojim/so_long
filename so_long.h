/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:34:45 by npederen          #+#    #+#             */
/*   Updated: 2025/03/30 16:15:11 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>	
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_app
{
	void	*mlx;
	void	*win;
	void	*img_player_up;
	void	*img_player_down;
	void	*img_player_left;
	void	*img_player_right;
	void	*img_background;
	void	*img_wall;
	void	*img_collectible;
	void	*img_island;
	void	*img_player_island;
	void	*img_exit;
	void	*img_exit_open;
	char	**map;
	int		rows_counter;
	int		cols_counter;
	int		players_counter;
	int		moves_counter;
	int		exits_counter;
	int		collectibles_counter;
	int		collected;
	int		coor_x;
	int		coor_y;
	int		exit_coor_x;
	int		exit_coor_y;
}	t_app;

void	game_init(t_app *game);
int		init_map(char *argv, t_app *game, int rows_counter);
void	init_mlx_images(t_app *game);
int		is_it_ber(char *file_name);
void	check_args(int argc, char **argv);
void	check_max_height(int lines_counter);
void	check_max_width(t_app *game);
void	handler_map_checker(char **argv, t_app *game);
void	handler_map_drawer(t_app *game);
void	handler_game(t_app *game);
int		handler_player(int key, void *param);
void	get_exit_xy(t_app *game);
int		is_tile_allowed(t_app *game, int x, int y);
void	update_boat_img(t_app *game, int nx, int ny, char key);
void	update_player_img(t_app *game, int nx, int ny, char key);
void	move_player(t_app *game, char key, int x, int y);
int		count_lines(char *argv);
void	count_key_tiles(t_app *game);
void	get_player_xy(t_app *game);
int		flood_fill(t_app *game, char **map, int x, int y);
void	are_key_tiles_reachable(t_app *game, char **argv);
int		check_row_length(char **map);
int		is_map_walled(t_app *game);
int		are_map_tiles_recognized(char **map);
void	map_tiles_checker(t_app *game);
void	free_map(char **map, t_app *game);
int		handler_exit_app(t_app *game);
void	draw_img(t_app *game, void *img, int x, int y);
void	update_player_xy(t_app *game, int x, int y);

# define IMG_PLAYER_UP "./images/boatU.xpm"
# define IMG_PLAYER_DOWN "./images/boatD.xpm"
# define IMG_PLAYER_LEFT "./images/boatL.xpm"
# define IMG_PLAYER_RIGHT "./images/boatR.xpm"
# define IMG_PLAYER_ISLAND "./images/vikingisland.xpm"
# define IMG_EXIT "./images/baril_vide2.xpm"
# define IMG_EXIT_OPEN "./images/baril_plein2.xpm"
# define IMG_COLLECTIBLE "./images/big_collectible.xpm"
# define IMG_ISLAND "./images/island.xpm"
# define IMG_WALL "./images/wall.xpm"
# define IMG_BACKGROUND "./images/water.xpm"
# define RES 32
# define MAP_MAXHEIGHT 63
# define MAP_MAXWIDTH 120

#endif