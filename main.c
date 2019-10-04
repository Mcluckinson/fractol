/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:42:53 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/05 00:10:50 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	usage(char *argv, int argc)
{
	if (argc != 2 || (!ft_strequ(argv, "julia") &&
	!ft_strequ(argv, "burning_ship") &&
	!ft_strequ(argv, "mandelbrot") &&
	!ft_strequ(argv, "mandelbar")))
	{
		ft_putstr("Usage: ./fractol + "
			"arg: mandelbrot/julia/mandelbar/burning_ship");
		exit(0);
	}
}

void		rangers_assemble(t_window *win, t_graphon *graphon, t_fract *frac)
{
	if (ft_strequ(frac->name, "mandelbrot"))
		draw_mandelbrot(graphon, frac, win);
	else if (ft_strequ(frac->name, "mandelbar"))
		draw_mandelbar(graphon, frac, win);
	else if (ft_strequ(frac->name, "julia"))
		draw_julia(graphon, frac, win);
	else if (ft_strequ(frac->name, "burning_ship"))
		draw_ship(graphon, frac, win);
}

void		go_go(t_window *win, char *name, t_graphon *graf, t_fract *frac)
{
	if (ft_strequ(name, "mandelbrot"))
		go_mandelbrot(win, graf, frac);
	else if (ft_strequ(name, "mandelbar"))
		go_mandelbar(win, graf, frac);
	else if (ft_strequ(name, "julia"))
	{
		go_julia(win, graf, frac);
		mlx_hook(win->win_ptr, 6, 1L << 6, julia_thingy, win);
	}
	else if (ft_strequ(name, "burning_ship"))
		go_ship(win, graf, frac);
}

int			main(int argc, char **argv)
{
	t_window		*window;
	t_graphon		*graphon;
	t_fract			*fractol;

	usage(argv[1], argc);
	if (!(graphon = ft_memalloc(sizeof(t_graphon))))
		return (-1);
	window = init_window();
	if (!(fractol = init_data()))
		return (-1);
	window->fractol = fractol;
	fractol->name = argv[1];
	start_cl(graphon);
	window->graphon = graphon;
	go_go(window, fractol->name, graphon, fractol);
	mlx_hook(window->win_ptr, 17, 1L << 17, close_window, window);
	mlx_hook(window->win_ptr, 2, 1L << 0, key_press, window);
	mlx_hook(window->win_ptr, 4, 1L << 2, mouse_buttons, window);
	mlx_loop(window->mlx_ptr);
}
