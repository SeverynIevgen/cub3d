/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:59:16 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 15:13:10 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_spaces(char **map, int rows)
{
	int i;
	int j;
	int line_up;
	int line_down;

	i = 1;
	while (i < rows - 1)
	{
		j = 1;
		line_up = ft_strlen(map[i - 1]);
		line_down = ft_strlen(map[i + 1]);
		while (map[i][j + 1])
		{
			if (!(not_wall(map[i][j])) ||
					(not_wall(map[i][j]) && map[i - 1][j] != ' ' &&
					map[i + 1][j] != ' ' && map[i][j - 1] != ' ' &&
					map[i][j + 1] != ' ' && j < line_up && j < line_down))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int		check_conf(char **map, int rows)
{
	int	i;
	int	j;
	int	last;
	int h;

	i = 0;
	h = 0;
	while (i < rows)
	{
		j = 0;
		last = ft_strlen(map[i]);
		while (j < last)
		{
			if (!(is_valid(map[i][j])))
				return (0);
			if (is_hero(map[i][j]))
				h++;
			j++;
		}
		i++;
	}
	return (h == 1 ? 1 : 0);
}

int		check_lr_cols(char **map, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		j = ft_strlen(map[i]) - 1;
		while (j >= 0)
		{
			while (map[i][j] == ' ')
				j--;
			if (map[i][j] != '1')
				return (0);
			else
				break ;
		}
		i++;
	}
	return (1);
}

int		check_fl_rows(char **map, int last)
{
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	while (map[last][j])
	{
		if (map[last][j] != '1' && map[last][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int		checking(t_data *game)
{
	if (!(check_fl_rows(game->map.arr, game->map.rows - 1)) ||
		!(check_lr_cols(game->map.arr, game->map.rows)) ||
		!(check_conf(game->map.arr, game->map.rows)) ||
		!(check_spaces(game->map.arr, game->map.rows)))
		return (exit_error(-13));
	else if (!(game->tex.n) || !(game->tex.s) || !(game->tex.e) ||
			!(game->tex.w) || !(game->tex.spr))
		return (exit_error(-14));
	else if (game->tex.ceil == 0xFF000000 || game->tex.fl == 0xFF000000)
		return (exit_error(-15));
	else if (!(game->wall.dist =
			(double *)malloc(sizeof(double) * game->win.width)))
		return (exit_error(-16));
	return (1);
}
