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

int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
static int	is_it_ber(char *file_name);
int			check_args(int argc, char **argv);
void	game_init(t_app *game);

#endif