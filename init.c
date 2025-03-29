/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:14:51 by npederen          #+#    #+#             */
/*   Updated: 2025/03/22 16:14:51 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_init(t_app *game)
{
	game->mlx = 0;
	game->win = 0;
	game->img_player_up = 0;
	game->img_player_down = 0;
	game->img_player_left = 0;
	game->img_player_right = 0;
	game->img_background = 0;
	game->img_wall = 0;
	game->img_collectible = 0;
	game->img_exit = 0;
	game->map = 0;
	game->tmp_map = 0;
	game->rows_counter = 0;
	game->cols_counter = 0;
	game->players_counter = 0;
	game->moves_counter = 0;
	game->exits_counter = 0;
	game->collectibles_counter = 0;
	game->collected = 0;
	game->coor_x = 0;
	game->coor_y = 0;
}

int	init_map(char *argv, t_app *game, int rows_counter)
{
	char	*line;
	int		i;
	int		fd;
	
	i = 0;
	line = 0;
	game->map = malloc(sizeof(char *) * (rows_counter + 1));
	if (!game->map)
		return (ft_putstr_fd("Error\nmalloc failed\n", 2), 1);
	fd = open(argv, O_RDONLY);
	while (i < rows_counter)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map[i] = ft_strtrim(line, "\n");
		free(line);
		if (!game->map[i])
			return (ft_putstr_fd("Error\nmalloc failed in ft_strtrim\n", 2),
				free_map(game->map, game), close(fd), 1);
		i++;
	}
	game->map[i] = NULL;
	close(fd);
	return (0);
}
