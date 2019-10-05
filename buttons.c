/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:00:07 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/05 16:05:32 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		close_window(t_window *window)
{
	del_win(window);
	exit(0);
}

int		key_press(int key, t_window *window)
{
	if (key == 53)
		close_window(window);
	if (key > 122 && key < 127)
	{
		arrow_fix(key, window->fractol);
		ft_bzero(window->img_data, MAP_W * UNIQ_BPP * MAP_H);
		rangers_assemble(window, window->graphon, window->fractol);
	}
	if (key == 69 || key == 24 || key == 78 || key == 27)
		fix_iterations(key, window);
	if (key == 49)
	{
		if (window->fractol->thingy_block == 0)
			window->fractol->thingy_block = 1;
		else
			window->fractol->thingy_block = 0;
	}
	if (key == 256)
	{
		ft_putnbr(window->fractol->max_iteration);
		ft_putchar('\n');
	}
	return (0);
}

int		mouse_buttons(int key, int x, int y, t_window *window)
{
	if (key == 4 || key == 5)
	{
		zoom_fix(key, window->fractol, x, y);
		ft_bzero(window->img_data, MAP_W * UNIQ_BPP * MAP_H);
		rangers_assemble(window, window->graphon, window->fractol);
	}
	return (0);
}

void	fix_iterations(int key, t_window *window)
{
	if (key == 69 || key == 24)
		window->fractol->max_iteration += 5;
	else if ((key == 78 || key == 27) && window->fractol->max_iteration > 4)
		window->fractol->max_iteration -= 5;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * MAP_H);
	rangers_assemble(window, window->graphon, window->fractol);
}
