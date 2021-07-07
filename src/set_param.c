/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:51:00 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/29 13:30:25 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			set_color(unsigned int *color, char *line, int i)
{
	int	r;
	int	g;
	int	b;

	if (*color != 0xFF000000)
		return (-10);
	i += spaces_out(line + i);
	r = ft_atoi(line + i);
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		i++;
	i += line[i] == ',' ? 1 + spaces_out(line + i + 1) : -i;
	g = ft_atoi(line + i);
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		i++;
	i += line[i] == ',' ? 1 + spaces_out(line + i + 1) : -i;
	b = ft_atoi(line + i);
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		i++;
	i += spaces_out(line + i);
	if (line[i] || r > 255 || g > 255 || b > 255)
		return (-18);
	*color = 256 * 256 * r + 256 * g + b;
	return (0);
}

int			game_texture(t_data *game, unsigned int **adr, char *line, int i)
{
	char	*xpm_file;
	int		j;
	int		len;

	if (*adr)
		return (-7);
	len = ft_strlen(line);
	while (spaces_out(line + len - 1))
		line[len-- - 1] = '\0';
	i += spaces_out(line + i);
	j = i;
	while (line[i])
		i++;
	if (!(xpm_file = (char *)malloc(sizeof(char) * (i - j + 1))))
		return (-8);
	i = j;
	j = 0;
	while (line[i])
		xpm_file[j++] = line[i++];
	xpm_file[j] = '\0';
	j = parse_xpm(game, adr, xpm_file);
	free(xpm_file);
	return (j == -1 ? -9 : 0);
}

int			set_resolution(t_data *game, char *line, int i)
{
	if (game->win.width != 0 || game->win.height != 0)
		return (-5);
	i += spaces_out(line + i);
	game->win.width = ft_atoi(line + i);
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		i++;
	i += spaces_out(line + i);
	game->win.height = ft_atoi(line + i);
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		i++;
	i += spaces_out(line + i);
	if (line[i] || game->win.width <= 0 || game->win.height <= 0)
		return (-6);
	if (game->win.width > 2560)
		game->win.width = 2560;
	if (game->win.height > 1400)
		game->win.height = 1400;
	return (0);
}

char		*get_row(t_data *game, char *line)
{
	char	*row;
	int		j;

	j = 0;
	if (!(row = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (NULL);
	while (line[j])
	{
		if (line[j] == '2')
			game->map.spr++;
		if (is_valid(line[j]))
			row[j] = line[j];
		else
			return (NULL);
		j++;
	}
	row[j] = '\0';
	return (row);
}

int			game_map(t_data *game, char *line)
{
	char	**map;
	int		j;

	j = 0;
	if (!(map = (char **)malloc(sizeof(char *) * (game->map.rows + 2))))
		return (-3);
	while (j < game->map.rows)
	{
		map[j] = game->map.arr[j];
		j++;
	}
	if (!(map[j] = get_row(game, line)))
	{
		free(map);
		return (-4);
	}
	map[++j] = NULL;
	if (game->map.rows)
		free(game->map.arr);
	game->map.arr = map;
	game->map.rows++;
	return (0);
}
