/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:29:13 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/29 13:03:18 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_error(int error)
{
	error == -1 ? write(2, "Error!\nCouldn't open the file.\n", 31) : 0;
	error == -2 ? write(2, "Couldn't parse the file.\n", 25) : 0;
	error == -3 ? write(2, "Error!\nMalloc error in map.\n", 28) : 0;
	error == -4 ? write(2, "Error!\nMap is not correct.\n", 27) : 0;
	error == -5 ? write(2, "Error!\nTwise specified resolution.\n", 35) : 0;
	error == -6 ? write(2, "Error!\nInvalid resolution.\n", 27) : 0;
	error == -7 ? write(2, "Error!\nTwise specified textures.\n", 33) : 0;
	error == -8 ? write(2, "Error!\nMalloc error in textures.\n", 33) : 0;
	error == -9 ? write(2, "Error!\nInvalid xpm-file/line.\n", 30) : 0;
	error == -10 ? write(2, "Error!\nTwise specified floor/ceiling.\n", 38) : 0;
	error == -11 ? write(2, "Error!\nIncorrect line.\n", 23) : 0;
	error == -12 ? write(2, "Error!\nMalloc error in sprites.\n", 32) : 0;
	error == -13 ? write(2, "Error!\nInvalid map.\n", 20) : 0;
	error == -14 ? write(2, "Error!\nTexture is missed.\n", 26) : 0;
	error == -15 ? write(2, "Error!\nFloor/ceiling color is missed.\n", 38) : 0;
	error == -16 ? write(2, "Error!\nMalloc error in distances.\n", 34) : 0;
	error == -17 ? write(2, "Error!\nCouldn't make screenshot.\n", 33) : 0;
	error == -18 ? write(2, "Error!\nFloor/ceiling color error.\n", 34) : 0;
	error == -19 ? write(2, "Error!\nExtra data after map.\n", 29) : 0;
	error == -20 ? write(2, "Error!\nMap is absent.\n", 22) : 0;
	return (-1);
}

int		not_wall(char c)
{
	return (c == '0' || c == '2' || c == 'N' ||
			c == 'S' || c == 'W' || c == 'E');
}

int		is_valid(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == '2' ||
		c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int		is_hero(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int		spaces_out(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' ||
			line[i] == '\v' || line[i] == '\r' || line[i] == '\f')
		i++;
	return (i);
}
