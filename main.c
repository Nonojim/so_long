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

int	handler_exit_app(t_app *game)
{
	free_map(game->map, game);
	mlx_destroy_image(game->mlx, game->img_player_up);
	mlx_destroy_image(game->mlx, game->img_player_down);
	mlx_destroy_image(game->mlx, game->img_player_left);
	mlx_destroy_image(game->mlx, game->img_player_right);
	mlx_destroy_image(game->mlx, game->img_exit);
	mlx_destroy_image(game->mlx, game->img_exit_open);
	mlx_destroy_image(game->mlx, game->img_collectible);
	mlx_destroy_image(game->mlx, game->img_island);
	mlx_destroy_image(game->mlx, game->img_background);
	mlx_destroy_image(game->mlx, game->img_wall);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
}

int	is_next_pos_ok(t_app *game, int x, int y)
{
	if (game->map[y][x] == '0')
		return (0);
	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'C')
		return (game->collected++, 0);
	if (game->map[y][x] == 'E' && (game->collected != game->collectibles_counter))
		return (1);
	if (game->map[y][x] == 'E' && (game->collected == game->collectibles_counter))
	{
		ft_putstr_fd("ur drunk\n", 1);
		handler_exit_app(game);
	}
	return (0);
}

void	update_p_move_img(t_app *game, int nx, int ny, char key)
{
	int	x;
	int	y;

	x = game->coor_x * 32;
	y = game->coor_y * 32;
	nx = nx * 32;
	ny = ny * 32;
	if (game->map[game->coor_y][game->coor_x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img_island, x, y);
	else if (game->map[game->coor_y][game->coor_x] == 'I')
		mlx_put_image_to_window(game->mlx, game->win, game->img_island, x, y);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img_background, x, y);
	if (key == 'W')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player_up, nx, ny);
	if (key == 'S')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player_down, nx, ny);
	if (key == 'A')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player_left, nx, ny);
	if (key == 'D')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player_right, nx, ny);
	game->moves_counter++;
	ft_putstr_fd("moves_counter: ", 1);
	ft_putnbr_fd(game->moves_counter, 1);
	ft_putstr_fd("\n", 1);
}

void	update_player_coordinates(t_app *game, int x, int y)
{
	game->coor_x = x;
	game->coor_y = y;
}

void	move_player(t_app *game, char key, int x, int y)
{
	if (key == 'W')
	{
		update_p_move_img(game, x, (y - 1), 'W');
		update_player_coordinates(game, x, (y - 1));
	}
	if (key == 'A')
	{
		update_p_move_img(game, (x - 1), y, 'A');
		update_player_coordinates(game, (x - 1), y);
	}
	if (key == 'S')
	{
		update_p_move_img(game, x, (y + 1), 'S');
		update_player_coordinates(game, x, (y + 1));
	}
	if (key == 'D')
	{
		update_p_move_img(game, (x + 1), y, 'D');
		update_player_coordinates(game, (x + 1), y);
	}
	printf("game->map[y][x] == %c", game->map[y][x]);
	if (game->map[y][x] == 'C' || game->map[y][x] == 'I')
		game->map[y][x] = 'I';
	else
		game->map[y][x] = '0';
}

int	handler_player_moves_counter(int key, void *param)
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
		&& is_next_pos_ok(game, x, (y - 1)) == 0)
		move_player(game, 'W', x, y);
	else if ((key == XK_a || key == XK_Left)
		&& is_next_pos_ok(game, (x - 1), y) == 0)
		move_player(game, 'A', x, y);
	else if ((key == XK_s || key == XK_Down)
		&& is_next_pos_ok(game, x, (y + 1)) == 0)
		move_player(game, 'S', x, y);
	else if ((key == XK_d || key == XK_Right)
		&& is_next_pos_ok(game, (x + 1), y) == 0)
		move_player(game, 'D', x, y);
	return (0);
}

static void	draw_img(t_app *game, void *img, int x, int y)
{
	x = x * 32;
	y = y * 32;
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
}

void	handler_map_draw(t_app *game)
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
			{
				//if (game->img_exit_open == NULL || game->img_exit == NULL)
				//{
    			//	fprintf(stderr, "One of the exit images is not initialized.\n");
    			//	exit(EXIT_FAILURE);
				//}
				//if (game->collectibles_counter == game->collected)
				//	draw_img(game, game->img_exit_open, x, y);
				//else
				draw_img(game, game->img_exit, x, y);
			}
			else if (game->map[y][x] == 'C')
				draw_img(game, game->img_island, x, y);
			else if (game->map[y][x] == '1')
				draw_img(game, game->img_wall, x, y);
			else if (game->map[y][x] == '0')
				draw_img(game, game->img_background, x, y);
			x++;
		}
		y++;
	}
}

void	init_images(t_app *game)
{
	int	w;
	int	h;

	w = 32;
	h = 32;
	game->img_player_up = mlx_xpm_file_to_image(game->mlx, IMG_PLAYER_UP, &w, &h);
	game->img_player_down = mlx_xpm_file_to_image(game->mlx, IMG_PLAYER_DOWN, &w, &h);
	game->img_player_left = mlx_xpm_file_to_image(game->mlx, IMG_PLAYER_LEFT, &w, &h);
	game->img_player_right = mlx_xpm_file_to_image(game->mlx, IMG_PLAYER_RIGHT, &w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, IMG_EXIT, &w, &h);
	game->img_exit_open = mlx_xpm_file_to_image(game->mlx, IMG_EXIT_OPEN, &w, &h);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx, IMG_COLLECTIBLE, &w, &h);
	game->img_island = mlx_xpm_file_to_image(game->mlx, IMG_ISLAND, &w, &h);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, IMG_WALL, &w, &h);
	game->img_background = mlx_xpm_file_to_image(game->mlx, IMG_BACKGROUND, &w, &h);
}

void	handler_game(t_app *game)
{
	game->mlx = mlx_init();
	init_images(game);
	game->win = mlx_new_window(game->mlx, game->cols_counter * 32,
			game->rows_counter * 32, "Non sense simulator");
	handler_map_draw(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, handler_player_moves_counter, game);
	mlx_hook(game->win, DestroyNotify, ButtonPressMask,	&handler_exit_app, game);
	mlx_loop(game->mlx);
}

void	handler_map_validator(char **argv, t_app *game)
{
	game->rows_counter = count_lines(argv[1]);
	init_map(argv[1], game, game->rows_counter);
	game->cols_counter = ft_strlen(game->map[0]);
	count_key_tiles(game);
	map_tiles_checker(game);
	are_key_tiles_reachable(game, argv);
}

int	main(int argc, char **argv)
{
	t_app	game;

	check_args(argc, argv);
	game_init(&game);
	handler_map_validator(argv, &game);
	handler_game(&game);
	handler_exit_app(&game);
	return (0);
}