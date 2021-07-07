/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:44:42 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/28 18:27:22 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi(char *line)
{
	int	i;
	int	numb;

	numb = 0;
	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		numb = numb * 10 + (line[i] - '0');
		i++;
	}
	return (numb);
}

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(char *src, int c)
{
	if (!src)
		return (NULL);
	if (c == 0)
		return ((char *)src + ft_strlen(src));
	while (*src)
	{
		if (*src == (char)c)
			return (src);
		src++;
	}
	return (NULL);
}
