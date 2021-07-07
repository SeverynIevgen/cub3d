/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:23:37 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/29 12:24:38 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hero_pos(t_data *game, int i, int j, char dir)
{
	game->pos.x = (double)j + 0.5;
	game->pos.y = (double)i + 0.5;
	if (dir == 'N')
		game->dir.angle = M_PI_2;
	else if (dir == 'W')
		game->dir.angle = M_PI;
	else if (dir == 'S')
		game->dir.angle = -M_PI_2;
	else if (dir == 'E')
		game->dir.angle = 0;
}

void	start_pos(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (game->map.arr[i][j])
		{
			if (is_hero(game->map.arr[i][j]))
			{
				hero_pos(game, i, j, game->map.arr[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
