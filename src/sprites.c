/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:18:33 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 20:56:20 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	pix_color(t_data *game, int index, unsigned int col, t_spr spr)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (col >= 0xFF000000 || col == 0x00000000 ||
		game->wall.dist[index % game->win.width] < spr.dist)
		return (game->img.adr[index]);
	t = col / (256 * 256 * 256);
	r = (col / (256 * 256) % 256) * (1 - (double)t / 256);
	g = (col / 256 % 256) * (1 - (double)t / 256);
	b = (col % 256) * (1 - (double)t / 256);
	r += (game->img.adr[index] / (256 * 256) % 256) * ((double)t / 256);
	g += (game->img.adr[index] / 256 % 256) * ((double)t / 256);
	b += (game->img.adr[index] % 256) * ((double)t / 256);
	return (r * 256 * 256 + g * 256 + b);
}

void			sprite_draw(t_data *game, int loc, t_spr sprite)
{
	unsigned int	col;
	double			size;
	int				index;
	int				i;
	int				j;

	i = 0;
	size = game->win.height / sprite.dist / 2;
	loc = loc - size / 2;
	while (i < size)
	{
		j = 0;
		while (loc + i >= 0 && loc + i < game->win.width && j < size)
		{
			col = 64 * (floor(64 * (double)j / size) + (double)i / size);
			col = game->tex.spr[col];
			index = loc + i + (game->win.height / 2 + j) * game->win.width;
			if (index < game->win.width * game->win.height)
				game->img.adr[index] = pix_color(game, index, col, sprite);
			j++;
		}
		i++;
	}
}

void			sprite_loc(t_data *game, t_spr sprite)
{
	double	angle;
	double	spr_x;
	double	spr_y;

	spr_x = (sprite.x - game->pos.x) / sprite.dist;
	spr_y = (sprite.y - game->pos.y) / sprite.dist;
	if (spr_y <= 0)
		angle = acos(spr_x) * 180 / M_PI;
	else
		angle = 360 - acos(spr_x) * 180 / M_PI;
	angle = game->dir.angle * 180 / M_PI - angle + AOV / 2;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	if (sprite.dist > 0.5)
		sprite_draw(game, angle * game->win.width / AOV, sprite);
}

void			sprites_sorting(t_data *game)
{
	t_spr	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < game->map.spr - 1)
	{
		j = i + 1;
		while (j < game->map.spr)
		{
			if (game->spr[j].dist > game->spr[i].dist)
			{
				tmp = game->spr[i];
				game->spr[i] = game->spr[j];
				game->spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void			sprites_config(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->map.spr)
		game->spr[i].dist =
			hypot(game->pos.x - game->spr[i].x, game->pos.y - game->spr[i].y);
	sprites_sorting(game);
	i = -1;
	while (++i < game->map.spr)
		sprite_loc(game, game->spr[i]);
}
