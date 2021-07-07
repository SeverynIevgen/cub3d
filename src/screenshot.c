/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:52:30 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 14:56:20 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pic_data(t_data *game, int fd)
{
	int				i;
	int				j;
	unsigned char	buff[4];

	i = game->win.width * (game->win.height - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < game->win.width)
		{
			buff[0] = (unsigned char)(game->img.adr[i] % 256);
			buff[1] = (unsigned char)(game->img.adr[i] / 256 % 256);
			buff[2] = (unsigned char)(game->img.adr[i] / 256 / 256 % 256);
			buff[3] = (unsigned char)(0);
			write(fd, buff, 4);
			i++;
			j++;
		}
		i -= 2 * game->win.width;
	}
}

void	pic_info(t_data *game, int fd)
{
	int				bytes;
	unsigned char	header[40];

	bytes = 0;
	while (bytes < 40)
		header[bytes++] = '\0';
	header[0] = '(';
	bytes = game->win.width;
	header[4] = (unsigned char)(bytes % 256);
	header[5] = (unsigned char)(bytes / 256 % 256);
	header[6] = (unsigned char)(bytes / 256 / 256 % 256);
	header[7] = (unsigned char)(bytes / 256 / 256 / 256);
	bytes = game->win.height;
	header[8] = (unsigned char)(bytes % 256);
	header[9] = (unsigned char)(bytes / 256 % 256);
	header[10] = (unsigned char)(bytes / 256 / 256 % 256);
	header[11] = (unsigned char)(bytes / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = ' ';
	write(fd, header, 40);
}

void	pic_header(t_data *game, int fd)
{
	int				bytes;
	unsigned char	bmp_header[14];

	bytes = 0;
	while (bytes < 14)
		bmp_header[bytes++] = '\0';
	bmp_header[0] = 'B';
	bmp_header[1] = 'M';
	bytes = 54 + 4 * game->win.width * game->win.height;
	bmp_header[2] = (unsigned char)(bytes % 256);
	bmp_header[3] = (unsigned char)(bytes / 256 % 256);
	bmp_header[4] = (unsigned char)(bytes / 256 / 256 % 256);
	bmp_header[5] = (unsigned char)(bytes / 256 / 256 / 256);
	bmp_header[10] = '6';
	write(fd, bmp_header, 14);
}

int		screenshot(t_data *game)
{
	int fd;
	int ret;

	ret = 1;
	game->ray.x = 0;
	game->ray.y = 0;
	game->ray.r = 0;
	game->ray.d = 0;
	game->ray.i = 0;
	game->wall.x = 0;
	game->wall.y = 0;
	make_image(game);
	if ((fd = open("cub3d.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND)) == -1)
		ret = -17;
	if (ret != -17)
	{
		pic_header(game, fd);
		pic_info(game, fd);
		pic_data(game, fd);
		close(fd);
	}
	free(game->img.ptr);
	free(game->img.adr);
	closing(game, 0);
	return (ret == 1 ? 1 : exit_error(ret));
}
