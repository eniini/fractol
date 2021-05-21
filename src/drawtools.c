/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawtools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:39:05 by eniini            #+#    #+#             */
/*   Updated: 2021/05/17 09:36:50 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Colorization tools for drawing fractals. Palette manipulation could include
**	a lot more fine-tuned user control, but without proper interface it doesn't
**	feel like worth the keybind-event-spaghetti.
*/

#include "fractol.h"

void	color_pixel(t_fract *data, int x, int y, int color)
{
	char		*dst;

	if ((y > 0 && x > 0) && (y < WIN_H && x < WIN_W))
	{
		dst = data->img.addr + (y * data->img.l_len + x * (data->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/*
**	Sine wave oscillation into hues
**	sin(frequency * increment (phase)) * amplitude (width) + offset (center)
**	As we're working with RGB system, [amplitude + offset] should never cross
**	over 255 and under 0.
*/

void	new_palette(t_fract *d)
{
	int		red;
	int		green;
	int		blue;
	int		i;

	i = 0;
	while (i < d->col.palettesize)
	{
		red = (int)(sin(d->col.freq_r * i + d->col.phase_r)
				* d->col.width + d->col.center);
		green = (int)(sin(d->col.freq_g * i + d->col.phase_g)
				* d->col.width + d->col.center);
		blue = (int)(sin(d->col.freq_b * i + d->col.phase_b)
				* d->col.width + d->col.center);
		d->col.palette[i] = (0 << 24 | red << 16 | green << 8 | blue);
		i++;
	}
}

/*
**	Offset sine wave frequencies for RGB channels to create randomized hues.
**	additionally, new hues are shifted 25 degrees in color space.
*/

void	shift_colors(t_fract *d)
{
	int	i;

	d->col.freq_r += 0.1;
	d->col.freq_g += 0.2;
	d->col.freq_b += 0.3;
	new_palette(d);
	i = 0;
	while (i < d->col.palettesize)
	{
		d->col.palette[i] = ft_hueshift(d->col.palette[i], 25.);
		i++;
	}
}
