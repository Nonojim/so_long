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
		return (write(2, "Error: malloc failed\n", 21), 0);
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
	return (1);
}

void	count_pecs(t_game *game)
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
			game->player++;
			else if (game->map[i][j] == 'E')
			game->exit++;
			else if (game->map[i][j] == 'C')
			game->amount_c++;
			j++;
		}
		i++;
	}
}

int	is_map_format_correct(t_app *game)
{
	if (game->amount_cols == game->rows_counter)
	{
		write(1, "ERROR : map must be rectangular.\n", 33);
		return (free_map(game->map, game), exit(1), 0);
	}
	if (are_map_rows_same_length(game->map) == 0)
	return (free_map(game->map, game), exit(1), 0);
	if (is_map_surrounded_by_1(game) == 0)
		return (free_map(game->map, game), exit(1), 0);
		if (are_map_attributs_valide(game->map) == 0)
		return (free_map(game->map, game), exit(1), 0);
		if (game->amount_c == 0 || game->player != 1 || game->exit != 1)
		{
			write(1, "ERROR : map rules not respected.\n", 33);
			return (free_map(game->map, game), exit(1), 0);
		}
		return (1);
	}
	int	are_map_rows_same_length(char **map)
	{
		int	i;
		
		if (!map)
		return (0);
		i = 1;
		while (map[i])
		{
			if (ft_strlen(map[0]) != ft_strlen(map[i]))
			{
				write(1, "ERROR : map has rows with iregular lenth.\n", 42);
				return (0);
			}
			i++;
		}
		return (1);
	}
	
	int	is_map_surrounded_by_1(t_app *game)
	{
		int	i;
		int	j;
		int	a_rows;
		int	a_cols;
		
		i = 0;
		j = 0;
		a_rows = game->rows_counter;
		a_cols = game->amount_cols;
		while (game->map[i])
		i++;
	while (j < a_cols)
	{
		if (game->map[0][j] != '1' || game->map[a_rows - 1][j] != '1')
		return (write(1, "1 ERROR : invalid surrounded walls\n", 35), 0);
		j++;
	}
	i = 1;
	while (i < a_rows - 1)
	{
		if (game->map[i][0] != '1' || game->map[i][a_cols - 1] != '1')
		return (write(1, "2 ERROR : invalid surrounded walls\n", 35), 0);
		i++;
	}
	return (1);
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
	return (0);
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
					return (0);
				}
				j++;
			}
			i++;
		}
		return (1);
	}

	void	handler_map_validator(char **argv, t_app *game)
	{
		game->rows_counter = count_lines(argv[1]);
		init_map(argv[1], game, game->rows_counter);
		game->amount_cols = ft_strlen(game->map[0]);
		count_pecs(game);
		is_map_format_correct(game);
		are_map_paths_valid(argv, game);
	}
	
	int	main(int argc, char **argv)
{
	t_app	game;

	check_args(argc, argv);
	game_init(&game);
	handler_map_validator(argv, &game);
	//handler_game(&game);
	//handler_exit_game(&game);
	return (0);
}