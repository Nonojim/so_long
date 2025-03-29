/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:12:00 by npederen          #+#    #+#             */
/*   Updated: 2025/03/29 16:55:18 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, t_app *game)
{
	int i;
	
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