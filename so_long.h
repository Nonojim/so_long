/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:34:45 by npederen          #+#    #+#             */
/*   Updated: 2025/03/22 13:34:45 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>	
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
# endif

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
	void	*img_exit;
	char	**map;
	char	**tmp_map;
	int		rows_counter;
	int		cols_counter;
	int		players_counter;
	int		moves_counter;
	int		exits_counter;
	int		collectibles_counter;
	int		collected;
	int		coor_x;
	int		coor_y;
}	t_app;

int		is_it_ber(char *file_name);
int		check_args(int argc, char **argv);
void	game_init(t_app *game);
int		count_lines(char *argv);
void	count_tiles(t_app *game);
int		init_map(char *argv, t_app *game, int rows_counter);
void	count_key_tiles(t_app *game);
int		map_tiles_checker(t_app *game);
int		check_row_length(char **map);
int		is_map_surrounded_by_1(t_app *game);
void	free_map(char **map, t_app *game);
int		are_map_attributs_valide(char **map);
void	handler_map_validator(char **argv, t_app *game);

#endif