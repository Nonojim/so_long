/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:47:38 by npederen          #+#    #+#             */
/*   Updated: 2025/03/30 11:16:52 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_exit_xy(t_app *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->rows_counter)
	{
		x = 0;
		while (x < game->cols_counter)
		{
			if (game->map[y][x] == 'E')
			{
				game->exit_coor_x = x;
				game->exit_coor_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

int	is_tile_allowed(t_app *game, int x, int y)
{
	if (game->map[y][x] == '0')
		return (0);
	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'C')
	{
		game->collected++;
		if (game->collected == game->collectibles_counter)
		{
			get_exit_xy(game);
			mlx_put_image_to_window(game->mlx, game->win, game->img_exit_open, \
			(game->exit_coor_x * RES), (game->exit_coor_y * RES));
		}
		return (0);
	}
	if (game->map[y][x] == 'E' && \
	(game->collected != game->collectibles_counter))
		return (1);
	if (game->map[y][x] == 'E' && \
	(game->collected == game->collectibles_counter))
	{
		ft_putstr_fd("ur drunk\n", 1);
		handler_exit_app(game);
	}
	return (0);
}

void	update_boat_img(t_app *game, int nx, int ny, char key)
{
	int	nxpx;
	int	nypx;

	nxpx = nx * RES;
	nypx = ny * RES;
	if (game->map[ny][nx] == 'C' || game->map[ny][nx] == 'I')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_player_island, nxpx, nypx);
	else if (key == 'W')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_player_up, nxpx, nypx);
	else if (key == 'S')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_player_down, nxpx, nypx);
	else if (key == 'A')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_player_left, nxpx, nypx);
	else if (key == 'D')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_player_right, nxpx, nypx);
}

void	update_player_img(t_app *game, int nx, int ny, char key)
{
	int	x;
	int	y;

	x = game->coor_x * RES;
	y = game->coor_y * RES;
	if (game->map[game->coor_y][game->coor_x] == 'C' \
	|| game->map[game->coor_y][game->coor_x] == 'I')
		mlx_put_image_to_window(game->mlx, game->win, game->img_island, x, y);
	else
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_background, x, y);
	update_boat_img(game, nx, ny, key);
	game->moves_counter++;
	ft_putstr_fd("moves_counter: ", 1);
	ft_putnbr_fd(game->moves_counter, 1);
	write(1, "\n", 1);
}

void	move_player(t_app *game, char key, int x, int y)
{
	if (key == 'W')
	{
		update_player_img(game, x, (y - 1), 'W');
		update_player_xy(game, x, (y - 1));
	}
	if (key == 'A')
	{
		update_player_img(game, (x - 1), y, 'A');
		update_player_xy(game, (x - 1), y);
	}
	if (key == 'S')
	{
		update_player_img(game, x, (y + 1), 'S');
		update_player_xy(game, x, (y + 1));
	}
	if (key == 'D')
	{
		update_player_img(game, (x + 1), y, 'D');
		update_player_xy(game, (x + 1), y);
	}
	if (game->map[y][x] == 'C' || game->map[y][x] == 'I')
		game->map[y][x] = 'I';
	else
		game->map[y][x] = '0';
}
