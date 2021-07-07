/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:03:16 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 15:11:37 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				fish_eye_cor(t_data *game)
{
	double	cor;
	double	f_eye;

	f_eye = fabs((double)game->ray.i / (game->win.width / 2) - 1) *
		28 * M_PI / 180;
	cor = (double)game->wall.dist[game->ray.i % game->win.width] * cos(f_eye);
	return (round(game->win.height / cor));
}

unsigned int	set_pixel(t_data *game, double line)
{
	int	index;
	int	vert;

	vert = game->ray.i % game->win.width;
	if (floor(game->wall.y) == game->wall.y)
	{
		index = 64 * (floor(64 * line) + game->wall.x - floor(game->wall.x));
		if (game->ray.d == 1)
			return (game->tex.s[index]);
		else
			return (game->tex.n[index]);
	}
	else if (floor(game->wall.x) == game->wall.x)
	{
		index = 64 * (floor(64 * line) + game->wall.y - floor(game->wall.y));
		if (game->ray.r == 1)
			return (game->tex.e[index]);
		else
			return (game->tex.w[index]);
	}
	return (0);
}

void			draw_line(t_data *game, int height)
{
	int				ceil;
	int				wall_p;
	unsigned int	color;

	ceil = game->win.width * (game->win.height - height) / 2;
	if (height > game->win.height)
		wall_p = (height - game->win.height) / 2;
	else
		wall_p = 0;
	color = game->tex.ceil;
	while (game->ray.i < game->win.width * game->win.height)
	{
		if (game->ray.i >= ceil && wall_p < height)
		{
			color = set_pixel(game, (double)wall_p / height);
			wall_p++;
		}
		else if (wall_p == height)
			color = game->tex.fl;
		game->img.adr[game->ray.i] = mlx_get_color_value(game->mlx.ptr, color);
		game->ray.i += game->win.width;
	}
	game->ray.i %= game->win.width;
}

void			make_image(t_data *game)
{
	int	bpp;
	int	l_len;
	int	end;

	game->img.ptr =
		mlx_new_image(game->mlx.ptr, game->win.width, game->win.height);
	game->img.adr =
		(unsigned int *)mlx_get_data_addr(game->img.ptr, &bpp, &l_len, &end);
	while (game->ray.i < game->win.width)
	{
		ray_calc(game);
		x_steps(game);
		y_steps(game);
		draw_line(game, fish_eye_cor(game));
		game->ray.i++;
	}
	sprites_config(game);
}

void			draw_screen(t_data *game)
{
	game->ray.x = 0;
	game->ray.y = 0;
	game->ray.r = 0;
	game->ray.d = 0;
	game->ray.i = 0;
	game->wall.x = 0;
	game->wall.y = 0;
	make_image(game);
	mlx_put_image_to_window(game->mlx.ptr, game->win.ptr, game->img.ptr, 0, 0);
	free(game->img.ptr);
	free(game->img.adr);
}
