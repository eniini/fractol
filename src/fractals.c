/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:06:41 by eniini            #+#    #+#             */
/*   Updated: 2021/05/13 17:51:22 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Calculates quadratic polynomials of known fractal sets for the given
**	x/y coordinates reprenting a complex value. Alternatively for Julia sets,
**	polynomials are solved using current mouse position in the program window.
**
**	Multi-sets calculate similar fractal set -dependent polynomials
**	but with a variable exponent.
*/

#include "fractol.h"

/*
**	Handles different complex calculations for the imaginary part
**	unique to each included fractal set.
*/

static double	do_comply(t_fract *d, double c_x, double c_y, double constant)
{
	if (d->shape.ship)
		return (fabs(2. * c_x * c_y) + constant);
	else if (d->shape.tricorn)
		return (-2. * c_x * c_y + constant);
	else
		return (2. * c_x * c_y + constant);
}

/*
**	Calculates all standard escape-time fractal sets, including their
**	Julia variants.
*/

double	calculate_fractal(t_fract *data, double complx, double comply)
{
	double	n;
	double	temp_x;
	double	constant_x;
	double	constant_y;

	constant_x = complx;
	constant_y = comply;
	if (data->shape.julia % 2)
	{
		constant_x = data->x;
		constant_y = data->y;
	}
	n = 0;
	while (n < data->precision && ((complx * complx) + (comply * comply)) < 4.)
	{
		temp_x = ((complx * complx) - (comply * comply)) + constant_x;
		comply = do_comply(data, complx, comply, constant_y);
		complx = temp_x;
		n++;
	}
	if (n == data->precision)
		return (n);
	return (n);
}

/*
**	Calculates Mandelbrot & Julia sets with a variable exponent.
**	The calculation is identical in its polynomial and bounding value except
**	for the exponent, which can be adjusted at will to either
**	negative or positive values.
**	
*/

static void	process_complexies(t_fract *d, double *complx, double *comply)
{
	double	coefficient;
	double	exponent;
	double	variable;

	if (d->shape.tricorn)
		variable = d->power / -2.;
	else
		variable = d->power / 2.;
	coefficient = pow((*complx * *complx) + (*comply * *comply), variable);
	exponent = d->power * atan2(*comply, *complx);
	*complx = coefficient * cos(exponent);
	if (d->shape.ship)
		*comply = fabs(coefficient * sin(exponent));
	else
		*comply = coefficient * sin(exponent);
}

double	calculate_multifractal(t_fract *data, double complx, double comply)
{
	double	n;
	double	constant_x;
	double	constant_y;

	constant_x = complx;
	constant_y = comply;
	if (data->shape.julia % 2)
	{
		constant_x = data->x;
		constant_y = data->y;
	}
	n = 0;
	while (n < data->precision && ((complx * complx) + (comply * comply)) < 4.)
	{
		process_complexies(data, &complx, &comply);
		complx += constant_x;
		comply += constant_y;
		n++;
	}
	return (n);
}
