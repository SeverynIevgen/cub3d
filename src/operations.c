/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:37:27 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/29 11:19:56 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_fb(double dir, t_data *game)
{
	double	dir_x;
	double	dir_y;

	dir_x = cos(game->dir.angle) * SPEED * dir;
	dir_y = -sin(game->dir.angle) * SPEED * dir;
	if (game->map.arr[(int)floor(game->pos.y)]
			[(int)floor(game->pos.x + dir_x)] != '1' &&
			game->map.arr[(int)floor(game->pos.y)]
			[(int)floor(game->pos.x + 2 * dir_x)] != '1')
		game->pos.x += dir_x;
	if (game->map.arr[(int)floor(game->pos.y + dir_y)]
			[(int)floor(game->pos.x)] != '1' &&
			game->map.arr[(int)floor(game->pos.y + 2 * dir_y)]
			[(int)floor(game->pos.x)] != '1')
		game->pos.y += dir_y;
}

void	move_lr(double dir, t_data *game)
{
	double	dir_x;
	double	dir_y;

	dir_x = -sin(game->dir.angle) * SPEED * dir;
	dir_y = -cos(game->dir.angle) * SPEED * dir;
	if (game->map.arr[(int)floor(game->pos.y)]
			[(int)floor(game->pos.x + dir_x)] != '1' &&
			game->map.arr[(int)floor(game->pos.y)]
			[(int)floor(game->pos.x + 2 * dir_x)] != '1')
		game->pos.x += dir_x;
	if (game->map.arr[(int)floor(game->pos.y + dir_y)]
			[(int)floor(game->pos.x)] != '1' &&
			game->map.arr[(int)floor(game->pos.y + 2 * dir_y)]
			[(int)floor(game->pos.x)] != '1')
		game->pos.y += dir_y;
}

int		closing(t_data *game, int mod)
{
	while (game->map.rows)
		free(game->map.arr[game->map.rows-- - 1]);
	free(game->map.arr);
	free(game->wall.dist);
	free(game->tex.n);
	free(game->tex.s);
	free(game->tex.e);
	free(game->tex.w);
	free(game->tex.spr);
	if (game->spr)
		free(game->spr);
	if (mod == 1)
		mlx_destroy_window(game->mlx.ptr, game->win.ptr);
	free(game->mlx.ptr);
	exit(0);
	return (1);
}

int		key_press(int key, t_data *game)
{
	if (key == ESC)
		closing(game, 1);
	if (key == LEFT || key == Q)
		game->dir.angle += ANGLE;
	if (key == FORW || key == W)
		move_fb(1, game);
	if (key == RIGHT || key == E)
		game->dir.angle -= ANGLE;
	if (key == BACK || key == S)
		move_fb(-1, game);
	if (key == A)
		move_lr(1, game);
	if (key == D)
		move_lr(-1, game);
	draw_screen(game);
	return (0);
}
