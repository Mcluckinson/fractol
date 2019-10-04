/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:42:53 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 12:42:55 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	usage(char *argv, int argc)
{
	if (argc != 2 || (!ft_strequ(argv, "julia") && !ft_strequ(argv, "burning_ship") && !ft_strequ(argv, "mandelbrot") && !ft_strequ(argv, "mandelbar")))
	{
		ft_putstr("Usage: ./fractol + arg: mandelbrot/julia/mandelbar/burning_ship");
		exit(0);
	}
}

void	rangers_assemble(t_window *window, t_graphon *graphon, t_fract *fractol)
{
	if (ft_strequ(fractol->name, "mandelbrot"))
		draw_mandelbrot(graphon, fractol, window);
	else if (ft_strequ(fractol->name, "mandelbar"))
		draw_mandelbar(graphon, fractol, window);
	else if (ft_strequ(fractol->name, "julia"))
		draw_julia(graphon, fractol, window);
	else if (ft_strequ(fractol->name, "burning_ship"))
		draw_ship(graphon, fractol, window);
}

void go_go_power_rangers(t_window *window, char *name, t_graphon *graphon, t_fract *fractol)
{
	if (ft_strequ(name, "mandelbrot"))
		go_mandelbrot(window, graphon, fractol);
	else if (ft_strequ(name, "mandelbar"))
		go_mandelbar(window, graphon, fractol);
	else if (ft_strequ(name, "julia"))
	{
		go_julia(window, graphon, fractol);
		mlx_hook(window->win_ptr, 6, 1L << 6, julia_thingy, window);
	}
	else if (ft_strequ(name, "burning_ship"))
		go_ship(window, graphon, fractol);
}

int	main(int argc, char **argv)
{
	t_window	*window;
	t_graphon	*graphon;
	t_fract	*fractol;

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
	go_go_power_rangers(window, fractol->name, graphon, fractol);
	mlx_hook(window->win_ptr, 17, 1L << 17, close_window, window);
	mlx_hook(window->win_ptr, 2, 1L << 0, key_press, window);
	mlx_hook(window->win_ptr, 4, 1L << 2, mouse_buttons, window);
	mlx_loop(window->mlx_ptr);
}
