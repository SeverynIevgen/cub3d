/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:49:05 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 15:58:32 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_correct(t_data *game, int x, int y)
{
	if (x < 0 || y < 0 || y > game->map.rows ||
			x >= ft_strlen(game->map.arr[y]))
		return (0);
	else if (game->map.arr[y][x] == ' ')
		return (0);
	return (1);
}

void		y_steps(t_data *game)
{
	double	x;
	double	y;

	y = floor(game->pos.y) + game->ray.d;
	x = game->pos.x + (y - game->pos.y) * (game->ray.x / game->ray.y);
	while (is_correct(game, (int)floor(x), (int)floor(y - 1 + game->ray.d)))
	{
		if (game->map.arr[(int)(y - 1 + game->ray.d)][(int)floor(x)] == '1')
		{
			if (game->wall.dist[game->ray.i] >
					hypot(x - game->pos.x, y - game->pos.y))
			{
				game->wall.x = x;
				game->wall.y = y;
				game->wall.dist[game->ray.i] =
					hypot(x - game->pos.x, y - game->pos.y);
			}
			return ;
		}
		x += (2 * game->ray.d - 1) * game->ray.x / game->ray.y;
		y += (2 * game->ray.d - 1);
	}
}

void		x_steps(t_data *game)
{
	double	x;
	double	y;

	x = floor(game->pos.x) + game->ray.r;
	y = game->pos.y + (x - game->pos.x) * (game->ray.y / game->ray.x);
	while (is_correct(game, (int)floor(x - 1 + game->ray.r), (int)floor(y)))
	{
		if (game->map.arr[(int)floor(y)][(int)floor(x - 1 + game->ray.r)]
				== '1')
		{
			game->wall.x = x;
			game->wall.y = y;
			game->wall.dist[game->ray.i] =
				hypot(x - game->pos.x, y - game->pos.y);
			return ;
		}
		x += (2 * game->ray.r - 1);
		y += (2 * game->ray.r - 1) * game->ray.y / game->ray.x;
	}
	game->wall.x = game->pos.x;
	game->wall.y = game->pos.y;
	game->wall.dist[game->ray.i] = 1000000000;
}

void		ray_calc(t_data *game)
{
	double	angle;

	angle = game->dir.angle + AOV * M_PI / 180 *
		(game->win.width / 2 - (double)game->ray.i) / game->win.width;
	game->ray.x = cos(angle);
	game->ray.y = -sin(angle);
	game->ray.r = 1;
	game->ray.d = 1;
	if (game->ray.x < 0)
		game->ray.r = 0;
	if (game->ray.y < 0)
		game->ray.d = 0;
}

int			sprites_list(t_data *game)
{
	int	i;
	int	j;
	int	sprites;

	if (game->spr)
		free(game->spr);
	if (!(game->spr = (t_spr *)malloc(sizeof(t_spr) * game->map.spr)))
		return (-1);
	sprites = 0;
	i = -1;
	while (++i < game->map.rows)
	{
		j = 0;
		while (game->map.arr[i][j])
		{
			if (game->map.arr[i][j] == '2')
			{
				game->spr[sprites].x = (double)j + 0.5;
				game->spr[sprites].y = (double)i + 0.5;
				sprites++;
			}
			j++;
		}
	}
	return (1);
}
