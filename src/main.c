/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:12:36 by eniini            #+#    #+#             */
/*   Updated: 2021/05/22 17:46:18 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Up to two parameters are expected for fractal sets to be drawn -
**	set name and if the fractal is desired to drawn with variable exponent
**	(multi-set variant). Julia set is included both as a parameter and a
**	toggleable feature due to the wording in the assignment.
*/

#include "fractol.h"

void	print_usage(void)
{
	ft_putendl("Usage: fractol [multi] <set>\n");
	ft_putstr("where <set> is one of\n\tmandelbrot | burning-ship | ");
	ft_putendl("tricorn | julia\n\n\tkeybinds:");
	ft_putendl("[J]\tswitches between static and dynamic (Julia) sets");
	ft_putendl("[Q/E]\tincreases/decreases multi-set exponent");
	ft_putendl("[N/M]\tincreases/decreases fractal precision");
	ft_putendl("[S]\tgenerates a new set of hues");
	ft_putendl("[R]\tresets fractal to its initial state");
	ft_putendl("[U]\tdisplay user interface");
	ft_putendl("[P]\tcaptures bitmap screenshot");
	exit(EXIT_SUCCESS);
}

void	reset_fractol(t_fract *data)
{
	data->render = (t_render){0., 0., 1.0};
	data->i_start = -1.;
	data->i_end = 1.;
	data->r_start = -1.5;
	data->r_end = 1.;
	data->precision = 100;
	data->power = 1.0;
	data->shape.julia = 0;
	data->scalar = 1.0;
	data->draw_ui = 0;
	data->col = (t_color){{0}, 50, .3, .3, .3, 0, 2, 4, 55, 200};
	new_palette(data);
}

void	check_argument(t_fract *data, int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		print_usage();
	if ((!ft_strcmp("Multi", argv[1]) || !ft_strcmp("multi", argv[1]))
		&& argc == 3)
		data->shape.multi = TRUE;
	if ((!ft_strcmp("Mandelbrot", argv[argc - 1])
			|| !ft_strcmp("mandelbrot", argv[argc - 1]))
		|| (!ft_strcmp("Julia", argv[argc - 1])
			|| !ft_strcmp("julia", argv[argc - 1])))
		data->shape.mandelbrot = TRUE;
	else if (!ft_strcmp("Burning-ship", argv[argc - 1])
		|| !ft_strcmp("burning-ship", argv[argc - 1]))
		data->shape.ship = TRUE;
	else if (!ft_strcmp("Tricorn", argv[argc - 1])
		|| !ft_strcmp("tricorn", argv[argc - 1]))
		data->shape.tricorn = TRUE;
	else
		print_usage();
}

t_fract	*init_fractol(int argc, char **argv)
{
	t_fract	*data;

	data = ft_memalloc(sizeof(t_fract));
	if (!data)
		ft_getout(strerror(errno));
	ft_memset(data, 0, sizeof(t_fract));
	check_argument(data, argc, argv);
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_getout("Failed to connect into X server");
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, APPNAME);
	if (!data->win)
		ft_getout("X server failed to create app window");
	return (data);
}

int	main(int argc, char **argv)
{
	t_fract	*data;

	data = init_fractol(argc, argv);
	reset_fractol(data);
	if (!ft_strcmp("Julia", argv[argc - 1])
		|| !ft_strcmp("julia", argv[argc - 1]))
		data->shape.julia++;
	mlx_hook(data->win, 02, (1L << 0), deal_keys, data);
	mlx_hook(data->win, 04, (1L << 2), deal_mousepress, data);
	mlx_hook(data->win, 06, (1L << 6), deal_mousemovement, data);
	mlx_loop_hook(data->mlx, drawloop, data);
	mlx_loop(data->mlx);
	return (0);
}
