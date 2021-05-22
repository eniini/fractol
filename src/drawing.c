/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:08:10 by eniini            #+#    #+#             */
/*   Updated: 2021/05/22 18:18:42 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	drawloop(t_fract *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.l_len, &data->img.endian);
	if (data->gfxinf)
		free(data->gfxinf);
	data->gfxinf = ft_init_1d_info(WIN_W, WIN_H, data->img.bpp, data->img.addr);
	draw_fractal(data);
	if (data->draw_ui % 2)
		draw_ui_bg(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	if (data->draw_ui % 2)
		draw_ui(data);
	return (0);
}

/*
**	Complex values are mapped into the current screen space range.
*/

static double	calculate_complexies(t_fract *d, double r_slope, double i_slope)
{
	double	complx;
	double	comply;

	complx = (d->r_start + r_slope * d->render.screen_x);
	comply = (d->i_start + i_slope * d->render.screen_y);
	if (d->shape.multi)
		return (calculate_multifractal(d, complx, comply));
	else
		return (calculate_fractal(d, complx, comply));
}

/*
**	Static ranges for imaginary and real dimensions are calculated beforehand.
*/

void	draw_fractal(t_fract *d)
{
	double	m;
	double	r_range;
	double	i_range;
	int		color;

	ft_bzero(d->img.addr, WIN_W * WIN_H * (d->img.bpp / 8));
	r_range = (d->r_end - d->r_start) / (double)WIN_W;
	i_range = (d->i_end - d->i_start) / (double)WIN_H;
	d->render.screen_x = 0;
	while (d->render.screen_x < WIN_W)
	{
		d->render.screen_y = 0;
		while (d->render.screen_y < WIN_H)
		{
			m = calculate_complexies(d, r_range, i_range);
			if (m == d->precision)
				color = 0x000000;
			else
				color = d->col.palette[(int)m % d->col.palettesize];
			color_pixel(d, d->render.screen_x, d->render.screen_y, color);
			d->render.screen_y++;
		}
		d->render.screen_x++;
	}
}
