/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:44:00 by npederen          #+#    #+#             */
/*   Updated: 2025/03/29 16:59:43 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char *argv)
{
	char	*line;
	int		lines_counter;
	int		fd;
	
	lines_counter = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		lines_counter++;
	}
	close(fd);
	if (lines_counter == 0)
	{
		ft_putstr_fd("Error\nMap file is empty\n", 2);
		exit(1);
	}
	return (lines_counter);
}

void	count_key_tiles(t_app *game)
{
	int	i;
	int	j;
	
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'P')
			game->players_counter++;
			else if (game->map[i][j] == 'E')
			game->exits_counter++;
			else if (game->map[i][j] == 'C')
			game->collectibles_counter++;
			j++;
		}
		i++;
	}
}

void	get_player_xy(t_app *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->rows_counter)
	{
		x = 0;
		while (x < game->cols_counter)
		{
			if (game->map[y][x] == 'P')
			{
				game->coor_x = x;
				game->coor_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

int	flood_fill(t_app *game, char **map, int x, int y)
{
	static int	collectible = 0;

	if (y < 0 || x < 0 || y >= game->rows_counter || x >= game->cols_counter || map[y][x] == '1' || map[y][x] == 'E')
		return (0);
	if (map[y][x] == 'C')
		collectible++;
	map[y][x] = '1';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
	if (collectible == (game->collectibles_counter))
		return (0);
	else
		return (1);
}


void	are_key_tiles_reachable(t_app *game, char **argv)
{
	t_app tmp;

	game_init(&tmp);
	if (init_map(argv[1], &tmp, game->rows_counter) == 1)
		return (free_map(tmp.map, game));
	get_player_xy(game);
	if (flood_fill(game, tmp.map, game->coor_x, game->coor_y) == 1)
	{
		ft_putstr_fd("Error\nkey tiles not reachable\n", 2);
		free_map(tmp.map, game);
		free_map(game->map, game);
		exit(1);
	}
	free_map(tmp.map, &tmp);
}
