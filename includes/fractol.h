/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:23:09 by eniini            #+#    #+#             */
/*   Updated: 2021/05/21 13:46:08 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <errno.h>
# include <string.h>

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include "ft_gfx.h"

# define APPNAME "fractol@eniini"

# define WH 0xffffff
# define UI	0xd11b1b

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			l_len;
	int			endian;
}				t_img;

typedef struct s_render
{
	int			screen_x;
	int			screen_y;
	long double	scale;
}				t_render;

typedef struct s_shape
{
	t_bool		mandelbrot;
	t_bool		ship;
	t_bool		tricorn;
	int			julia;
	t_bool		multi;
}				t_shape;

typedef struct s_color
{
	int			palette[50];
	int			palettesize;
	float		freq_r;
	float		freq_g;
	float		freq_b;
	int			phase_r;
	int			phase_g;
	int			phase_b;
	int			width;
	int			center;
}				t_color;

typedef struct s_fract
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_render	render;
	t_shape		shape;
	t_color		col;
	double		power;
	double		precision;
	double		x;
	double		y;
	double		i_start;
	double		i_end;
	double		r_start;
	double		r_end;
	double		scalar;
	int			draw_ui;
}				t_fract;

//main.c
void	reset_fractol(t_fract *data);

//events.c
int		deal_mousepress(int mkpress, int x, int y, t_fract *data);
int		deal_mousemovement(int x, int y, t_fract *data);
int		deal_keys(int keypress, t_fract *data);

//drawing.c
int		drawloop(t_fract *data);
void	draw_fractal(t_fract *data);

//fractals.c
double	calculate_fractal(t_fract *data, double complx, double comply);
double	calculate_multifractal(t_fract *data, double complx, double comply);

//drawtools.c
void	color_pixel(t_fract *data, int x, int y, int color);
void	new_palette(t_fract *d);
void	shift_colors(t_fract *d);

//interface.c
void	draw_ui_bg(t_fract *d);
void	draw_ui(t_fract *d);

#endif