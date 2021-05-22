/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:07:32 by eniini            #+#    #+#             */
/*   Updated: 2021/05/22 18:18:45 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Calculates exact position of cursor inside the complex plane
**	for Julia calculations.
*/

int	deal_mousemovement(int x, int y, t_fract *data)
{
	data->x = ft_d_lerp(data->r_start, data->r_end, (double)x / WIN_W);
	data->y = ft_d_lerp(data->i_start, data->i_end, (double)y / WIN_H);
	return (0);
}

/*
**	Handles mousewheel inputs to zoom in and out the fractal.
**	Shift_x/y is the offset used to calculate new drawn area
*/

int	deal_mousepress(int mkpress, int x, int y, t_fract *d)
{
	double	shift_x;
	double	shift_y;

	shift_x = (double)x * ((d->r_end - d->r_start) / WIN_W) + d->r_start;
	shift_y = (double)y * ((d->i_end - d->i_start) / WIN_H) + d->i_start;
	if (mkpress == 4)
	{
		d->render.scale *= 0.9;
		d->scalar *= 1.1;
		d->r_end = d->r_end * 0.9 + shift_x * 0.1;
		d->r_start = d->r_start * 0.9 + shift_x * 0.1;
		d->i_end = d->i_end * 0.9 + shift_y * 0.1;
		d->i_start = d->i_start * 0.9 + shift_y * 0.1;
	}
	if (mkpress == 5 && d->render.scale <= 1.5)
	{
		d->render.scale *= 1.1;
		d->scalar *= 0.9;
		d->r_end = d->r_end * 1.1 + shift_x * -0.1;
		d->r_start = d->r_start * 1.1 + shift_x * -0.1;
		d->i_end = d->i_end * 1.1 + shift_y * -0.1;
		d->i_start = d->i_start * 1.1 + shift_y * -0.1;
	}
	return (0);
}

/*
**	Arrowkeys to move drawn area around the window.
**	Creates the effect of moving around the fractal when zoomed in.
*/

static int	deal_directionalkeys(int keypress, t_fract *data)
{
	if (keypress == 0xff52)
	{
		data->i_end -= 0.1 * data->render.scale;
		data->i_start -= 0.1 * data->render.scale;
	}
	if (keypress == 0xff54)
	{
		data->i_end += 0.1 * data->render.scale;
		data->i_start += 0.1 * data->render.scale;
	}
	if (keypress == 0xff51)
	{
		data->r_end -= 0.1 * data->render.scale;
		data->r_start -= 0.1 * data->render.scale;
	}
	if (keypress == 0xff53)
	{
		data->r_end += 0.1 * data->render.scale;
		data->r_start += 0.1 * data->render.scale;
	}
	return (0);
}

/*
**	[J] to shift into julia sets and back
**	[Q/E] to lower & raise multi-set exponent
**	[N/M] increases/decreases precision
**	[S] generates a new palette of hues
**	[R] resets the fractal to its initial state
**	[P] captures screenshot
*/

static int	deal_extrakeys(int keypress, t_fract *data)
{
	if (keypress == 0x70)
	{
		if ((ft_create_bmp("screenshot.bmp", data->gfxinf)))
			ft_getout(strerror(errno));
		ft_putendl("screenshot created!");
	}
	return (deal_directionalkeys(keypress, data));
}

int	deal_keys(int keypress, t_fract *data)
{
	if (keypress == 0x6a)
		data->shape.julia++;
	if (keypress == 0xff1b)
		exit(EXIT_SUCCESS);
	if (keypress == 0x71)
		data->power -= 0.1;
	if (keypress == 0x65)
		data->power += 0.1;
	if (keypress == 0x6d)
	{
		if (data->precision < 1000.)
			data->precision += 50.;
	}
	if (keypress == 0x6e)
	{
		if (data->precision > 0.)
			data->precision -= 50.;
	}
	if (keypress == 0x75)
		data->draw_ui++;
	if (keypress == 0x73)
		shift_colors(data);
	if (keypress == 0x72)
		reset_fractol(data);
	return (deal_extrakeys(keypress, data));
}
