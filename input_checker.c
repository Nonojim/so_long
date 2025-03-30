/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:09:27 by npederen          #+#    #+#             */
/*   Updated: 2025/03/30 16:13:57 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_it_ber(char *file_name)
{
	int	i;

	i = 0;
	if (!file_name)
		return (0);
	i = ft_strlen(file_name) - 1;
	if (file_name[i] == 'r' && file_name[i - 1] == 'e'
		&& file_name[i - 2] == 'b' && file_name[i - 3] == '.' )
		return (1);
	return (0);
}

void	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nfollow example: <./so_long> <map.ber>\n", 2);
		exit (1);
	}
	if (is_it_ber(argv[1]) != 1)
	{
		ft_putstr_fd("Error\nnot a .ber\n", 2);
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nfailed to open .ber file\n", 2);
		close(fd);
		exit (1);
	}
	else
		close(fd);
}

void	check_max_width(t_app *game)
{
	if (game->cols_counter > MAP_MAXWIDTH)
	{
		ft_putstr_fd("Error\nMap max width reached, shorten your map\n", 2);
		free_map(game->map, game);
		exit(1);
	}
}

void	check_max_height(int lines_counter)
{
	if (lines_counter > MAP_MAXHEIGHT)
	{
		ft_putstr_fd("Error\nMap max height reached, shorten your map\n", 2);
		exit(1);
	}
}
