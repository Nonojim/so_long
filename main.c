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

int	main(int argc, char **argv)
{
	t_app	game;

	check_args(argc, argv);
	game_init(&game);
	game.mlx = mlx_init();
    if (!game.mlx)
        return (write(2, "Error: MLX init failed\n", 23), 1);

		game.win = mlx_new_window(game.mlx, 800, 600, "so_long");
    if (!game.win)
        return (write(2, "Error: Window creation failed\n", 30), 1);

    mlx_loop(game.mlx); // Boucle principale pour gérer les événements
		//handler_map_validator(argv, &game);
		//handler_game(&game);
		//handler_exit_game(&game);
	return (0);
}