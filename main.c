/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:33:15 by npederen          #+#    #+#             */
/*   Updated: 2025/03/30 16:06:06 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handler_map_checker(char **argv, t_app *game)
{
	game->rows_counter = count_lines(argv[1]);
	init_map(argv[1], game, game->rows_counter);
	game->cols_counter = ft_strlen(game->map[0]);
	check_max_width(game);
	count_key_tiles(game);
	map_tiles_checker(game);
	are_key_tiles_reachable(game, argv);
}

void	handler_map_drawer(t_app *game)
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
				draw_img(game, game->img_player_right, x, y);
			else if (game->map[y][x] == 'E')
				draw_img(game, game->img_exit, x, y);
			else if (game->map[y][x] == 'C')
				draw_img(game, game->img_collectible, x, y);
			else if (game->map[y][x] == '1')
				draw_img(game, game->img_wall, x, y);
			else if (game->map[y][x] == '0')
				draw_img(game, game->img_background, x, y);
			x++;
		}
		y++;
	}
}

int	handler_player(int key, void *param)
{
	int		x;
	int		y;
	t_app	*game;

	game = (t_app *)param;
	x = game->coor_x;
	y = game->coor_y;
	if (key == XK_Escape)
		handler_exit_app(game);
	else if ((key == XK_w || key == XK_Up)
		&& is_tile_allowed(game, x, (y - 1)) == 0)
		move_player(game, 'W', x, y);
	else if ((key == XK_a || key == XK_Left)
		&& is_tile_allowed(game, (x - 1), y) == 0)
		move_player(game, 'A', x, y);
	else if ((key == XK_s || key == XK_Down)
		&& is_tile_allowed(game, x, (y + 1)) == 0)
		move_player(game, 'S', x, y);
	else if ((key == XK_d || key == XK_Right)
		&& is_tile_allowed(game, (x + 1), y) == 0)
		move_player(game, 'D', x, y);
	return (0);
}

void	handler_game(t_app *game)
{
	game->mlx = mlx_init();
	init_mlx_images(game);
	game->win = mlx_new_window(game->mlx, game->cols_counter * RES,
			game->rows_counter * RES, "Non sense simulator");
	handler_map_drawer(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, \
		handler_player, game);
	mlx_hook(game->win, DestroyNotify, ButtonPressMask, \
	&handler_exit_app, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_app	game;

	check_args(argc, argv);
	game_init(&game);
	handler_map_checker(argv, &game);
	handler_game(&game);
	handler_exit_app(&game);
	return (0);
}
