/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:33:15 by npederen          #+#    #+#             */
/*   Updated: 2025/03/22 13:33:15 by npederen         ###   ########.fr       */
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
	return (lines_counter);
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
		return (write(2, "Error: malloc failed\n", 21), 1);
	fd = open(argv, O_RDONLY);
	while (i < rows_counter)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map[i] = ft_strtrim(line, "\n");
		free(line);
		if (!game->map[i])
			return (write(2, "Error: malloc failed in ft_strtrim\n", 35),
				free_map(game->map, game), close(fd), 0);
		i++;
	}
	game->map[i] = NULL;
	close(fd);
	return (0);
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

int	map_tiles_checker(t_app *game)
{
	if (check_row_length(game->map) == 1)
	{
		free_map(game->map, game);
		(exit(1));
	}
	if (is_map_surrounded_by_1(game) == 1)
	{
		free_map(game->map, game);
		(exit(1));
	}
	if (are_map_attributs_valide(game->map) == 1)
	{
		free_map(game->map, game);
		(exit(1));
	}
	if (game->collectibles_counter == 0 || game->players_counter != 1 || game->exits_counter != 1)
	{
		write(1, "ERROR : map rules not respected.\n", 33);
		free_map(game->map, game);
		(exit(1));
	}
	return (0);
}

int	check_row_length(char **map)
{
	int	i;
	
	if (!map)
		return (1);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[0]) != ft_strlen(map[i]))
		{
			write(1, "ERROR : map has rows with iregular lenth.\n", 42);
			return (1);
		}
		i++;
	}
	return (0);
}
	
int	is_map_surrounded_by_1(t_app *game)
{
	int	i;
	int	j;
	int	rows_counter;
	int	cols_counter;
	
	i = 0;
	j = 0;
	rows_counter = game->rows_counter;
	cols_counter = game->cols_counter;
	while (game->map[i])
	i++;
	while (j < cols_counter)
	{
		if (game->map[0][j] != '1' || game->map[rows_counter - 1][j] != '1')
			return (write(1, "1 ERROR : invalid surrounded walls\n", 35), 1);
		j++;
	}
	i = 1;
	while (i < rows_counter - 1)
	{
		if (game->map[i][0] != '1' || game->map[i][cols_counter - 1] != '1')
			return (write(1, "2 ERROR : invalid surrounded walls\n", 35), 1);
		i++;
	}
	return (0);
}

void	free_map(char **map, t_app *game)
{
	int i;
	
	if (!map)
	{
		write(1, "ERROR: free_map, empty map\n", 27);
		return ;
	}
	i = 0;
	while (i < game->rows_counter)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

int	are_map_attributs_valide(char **map)
{
	int	i;
	int	j;
	
	if (!map)
		return (1);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j]
				!= 'C' && map[i][j] != '0' && map[i][j] != '1')
				{
					write(1, "ERROR : map has invalide attributs.\n", 36);
					return (1);
				}
				j++;
			}
			i++;
		}
		return (0);
}

int	flood_fill(t_app *game, char **map, int x, int y)
{
	static int	collectible = 0;

	if (y < 0 || x < 0 || y >= game->rows_counter || x >= game->cols_counter || map[y][x] == '1')
		return (0);
	if (map[y][x] == 'C' || map[y][x] == 'E')
		collectible++;
	map[y][x] = '1';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
	if (collectible == (game->collectibles_counter + 1))
		return (0);
	else
		return (1);
}

void	handler_map_validator(char **argv, t_app *game)
{
	game->rows_counter = count_lines(argv[1]);
	init_map(argv[1], &game, game->rows_counter);
	game->cols_counter = ft_strlen(game->map[0]);
	count_key_tiles(&game);
	map_tiles_checker(&game);
	are_key_tiles_reachable(&game);
}

int	main(int argc, char **argv)
{
	t_app	game;

	check_args(argc, argv);
	game_init(&game);
	handler_map_validator(argv, &game);
	//handler_game(&game);
	//handler_exits_counter_app(&game);
	return (0);
}