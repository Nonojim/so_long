/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:12:00 by npederen          #+#    #+#             */
/*   Updated: 2025/03/30 04:57:00 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, t_app *game)
{
	int	i;

	if (!map)
	{
		ft_putstr_fd("Error\nfree_map, empty map\n", 2);
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
	mlx_destroy_image(game->mlx, game->img_player_island);
	mlx_destroy_image(game->mlx, game->img_background);
	mlx_destroy_image(game->mlx, game->img_wall);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
}

void	draw_img(t_app *game, void *img, int x, int y)
{
	x = x * RES;
	y = y * RES;
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
}

void	update_player_coordinates(t_app *game, int x, int y)
{
	game->coor_x = x;
	game->coor_y = y;
}
