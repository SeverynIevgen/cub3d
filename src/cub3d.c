/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:09:04 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 12:28:47 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		start_init(t_data game, char *file, int mod)
{
	game.pos.x = 0;
	game.pos.y = 0;
	game.dir.angle = 0;
	game.mlx.ptr = mlx_init();
	if (parse_cub(&game, file) == -1)
		return (closing(&game, 0));
	if (mod == 1 && screenshot(&game) == -1)
		return (1);
	game.win.ptr =
		mlx_new_window(game.mlx.ptr, game.win.width, game.win.height, "Cub 3D");
	draw_screen(&game);
	mlx_hook(game.win.ptr, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win.ptr, 17, 1L << 0, closing, &game);
	mlx_loop(game.mlx.ptr);
	return (1);
}

void	cub_init(char *file, int bmp)
{
	t_data	game;

	game.mlx.ptr = NULL;
	game.win.ptr = NULL;
	game.win.width = 0;
	game.win.height = 0;
	game.img.ptr = NULL;
	game.img.adr = NULL;
	game.map.arr = NULL;
	game.map.rows = 0;
	game.map.spr = 0;
	game.tex.n = NULL;
	game.tex.s = NULL;
	game.tex.e = NULL;
	game.tex.w = NULL;
	game.tex.spr = NULL;
	game.tex.ceil = 0xFF000000;
	game.tex.fl = 0xFF000000;
	game.spr = NULL;
	game.wall.x = 0;
	game.wall.y = 0;
	game.wall.dist = NULL;
	start_init(game, file, bmp);
}

int		check_save(char *arg, char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (arg[i] != name[i])
			return (0);
		i++;
	}
	if (arg[i])
		return (0);
	return (1);
}

int		check_file(char *arg, char *name)
{
	int	i;

	i = ft_strlen(arg);
	if (i > 4 && arg[i - 1] == name[3] && arg[i - 2] == name[2] &&
			arg[i - 3] == name[1] && arg[i - 4] == name[0])
		return (1);
	return (0);
}

int		main(int argc, char *argv[])
{
	if (argc == 3 && check_file(argv[1], ".cub") &&
			check_save(argv[2], "--save"))
		cub_init(argv[1], 1);
	else if (argc == 2 && check_file(argv[1], ".cub"))
		cub_init(argv[1], 0);
	else
		write(2, "Error!\nInvalid arguments.\n", 26);
	return (0);
}
