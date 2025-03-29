/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:46:50 by npederen          #+#    #+#             */
/*   Updated: 2025/03/29 16:58:09 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			ft_putstr_fd("Error\nmap has rows with irregular length\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
	
int	is_map_walled(t_app *game)
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
			return (ft_putstr_fd("Error\nmap is not walled\n", 2), 1);
		j++;
	}
	i = 1;
	while (i < rows_counter - 1)
	{
		if (game->map[i][0] != '1' || game->map[i][cols_counter - 1] != '1')
			return (ft_putstr_fd("Error\nmap is not walled\n", 2), 1);
		i++;
	}
	return (0);
}

int	are_map_tiles_recognize(char **map)
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
					ft_putstr_fd("Error\nmap has invalide attributs\n", 2);
					return (1);
				}
				j++;
			}
			i++;
		}
		return (0);
}

int	map_tiles_checker(t_app *game)
{
	if (check_row_length(game->map) == 1)
	{
		free_map(game->map, game);
		(exit(1));
	}
	if (is_map_walled(game) == 1)
	{
		free_map(game->map, game);
		(exit(1));
	}
	if (are_map_tiles_recognize(game->map) == 1)
	{
		free_map(game->map, game);
		(exit(1));
	}
	if (game->collectibles_counter == 0 || game->players_counter != 1 || game->exits_counter != 1)
	{
		ft_putstr_fd("Error\nmap rules not respected\n", 2);
		free_map(game->map, game);
		(exit(1));
	}
	return (0);
}