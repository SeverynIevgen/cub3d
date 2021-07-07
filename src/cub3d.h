/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:46:14 by zdawnsta          #+#    #+#             */
/*   Updated: 2020/09/29 12:28:51 by zdawnsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "./mlx.h"

# define SPEED 0.2
# define AOV 66
# define ANGLE M_PI / 60

# define ESC 53
# define LEFT 123
# define FORW 126
# define RIGHT 124
# define BACK 125
# define ENTER 36
# define Q 12
# define W 13
# define E 14
# define A 0
# define S 1
# define D 2

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_dir
{
	double	angle;
}				t_dir;

typedef struct	s_ray
{
	double	x;
	double	y;
	double	r;
	double	d;
	int		i;
}				t_ray;

typedef struct	s_wall
{
	double	x;
	double	y;
	double	*dist;
}				t_wall;

typedef struct	s_spr
{
	double	x;
	double	y;
	double	dist;
}				t_spr;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*spr;
	unsigned int	ceil;
	unsigned int	fl;
}				t_tex;

typedef struct	s_map
{
	char	**arr;
	int		rows;
	int		spr;
}				t_map;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
}				t_img;

typedef struct	s_win
{
	void	*ptr;
	int		width;
	int		height;
}				t_win;

typedef struct	s_mlx
{
	void	*ptr;
}				t_mlx;

typedef struct	s_data
{
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_map	map;
	t_tex	tex;
	t_pos	pos;
	t_dir	dir;
	t_ray	ray;
	t_wall	wall;
	t_spr	*spr;
	int		error;
}				t_data;

int				ft_atoi(char *line);
int				ft_strlen(const char *str);
char			*ft_strdup(const char *src);
char			*ft_strchr(char *src, int c);

void			move_fb(double dir, t_data *game);
void			move_lr(double dir, t_data *game);
int				closing(t_data *game, int mod);
int				key_press(int key, t_data *game);

int				exit_error(int error);
int				not_wall(char c);
int				is_valid(char c);
int				is_hero(char c);
int				spaces_out(char *line);

unsigned int	pix_color(t_data *game, int index, unsigned int col, t_spr spr);
void			sprite_draw(t_data *game, int loc, t_spr sprite);
void			sprite_loc(t_data *game, t_spr sprite);
void			sprites_sorting(t_data *game);
void			sprites_config(t_data *game);

int				is_correct(t_data *game, int x, int y);
void			y_steps(t_data *game);
void			x_steps(t_data *game);
void			ray_calc(t_data *game);
int				sprites_list(t_data *game);

int				fish_eye_cor(t_data *game);
unsigned int	set_pixel(t_data *game, double line);
void			draw_line(t_data *game, int height);
void			make_image(t_data *game);
void			draw_screen(t_data *game);

void			pic_data(t_data *game, int fd);
void			pic_info(t_data *game, int fd);
void			pic_header(t_data *game, int fd);
int				screenshot(t_data *game);

int				check_spaces(char **map, int rows);
int				check_conf(char **map, int rows);
int				check_lr_cols(char **map, int rows);
int				check_fl_rows(char **map, int last);
int				checking(t_data *game);

char			*join_str(char *line, char *buff);
int				get_line(char **line, char **lines, char *new_line);
int				check_rem(char **line, char **lines);
int				get_next_line(int fd, char **line);

int				set_color(unsigned int *color, char *line, int i);
int				game_texture(t_data *game,
				unsigned int **adr, char *line, int i);
int				set_resolution(t_data *game, char *line, int i);
char			*get_row(t_data *game, char *line);
int				game_map(t_data *game, char *line);

void			hero_pos(t_data *game, int i, int j, char dir);
void			start_pos(t_data *game);

int				parse_xpm(t_data *game, unsigned int **adr, char *xpm_file);
int				parse_parameters(t_data *game, char *line);
int				parse_line(t_data *game, char *line);
int				parse_cub(t_data *game, char *file);

int				start_init(t_data game, char *file, int mod);
void			cub_init(char *file, int bmp);
int				check_save(char *arg, char *name);
int				check_file(char *arg, char *name);

#endif
