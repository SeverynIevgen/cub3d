/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:47:04 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/29 13:05:22 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_xpm(t_data *game, unsigned int **adr, char *xpm_file)
{
	void	*img;
	int		fd;
	int		arr[5];

	if (check_file(xpm_file, ".xpm") == 0)
		return (-1);
	if ((fd = open(xpm_file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(game->mlx.ptr, xpm_file, &arr[0], &arr[1]);
	if (!img || arr[0] != 64 || arr[1] != 64)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &arr[2], &arr[3], &arr[4]);
	free(img);
	return (0);
}

int		parse_parameters(t_data *game, char *line)
{
	int	i;

	i = spaces_out(line);
	if (line[i] == 'R' && line[i + 1] == ' ')
		game->error = set_resolution(game, line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		game->error = game_texture(game, &game->tex.spr, line, i + 2);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		game->error = game_texture(game, &game->tex.n, line, i + 3);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		game->error = game_texture(game, &game->tex.s, line, i + 3);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		game->error = game_texture(game, &game->tex.w, line, i + 3);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		game->error = game_texture(game, &game->tex.e, line, i + 3);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		game->error = set_color(&game->tex.ceil, line, i + 2);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		game->error = set_color(&game->tex.fl, line, i + 2);
	else if (line[i] != '\0')
		game->error = -11;
	return (game->error);
}

int		parse_line(t_data *game, char *line)
{
	int	i;

	i = spaces_out(line);
	if (game->error == 0 && line[i] == '1')
		game->error = game_map(game, line);
	else if (game->map.rows == 0)
		game->error = parse_parameters(game, line);
	else if (line[i] == '\0' && game->error >= 0)
		game->error = 1;
	else
		return (exit_error(-19));
	return (game->error < 0 ? exit_error(game->error) : 0);
}

int		parse_cub(t_data *game, char *file)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (exit_error(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (parse_line(game, line) == -1)
			ret = 2;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == 2)
		return (exit_error(ret - 1));
	if (game->map.rows == 0)
		return (exit_error(-20));
	start_pos(game);
	if (sprites_list(game) == -1)
		return (exit_error(-12));
	return (checking(game));
}
