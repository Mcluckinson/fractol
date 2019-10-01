/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:00:07 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/01 12:53:34 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int             close_window(t_window *window)
{
	del_win(window);
	exit(0);
}

void			del_win(t_window *window)
{
	if (window && window->win_ptr)
		free(window->win_ptr);
	if (window && window->mlx_ptr)
		free(window->mlx_ptr);
	if (window && window->img_ptr)
		free(window->img_ptr);
	if (window && window->linesize)
		free(window->linesize);
	if (window && window->endian)
		free(window->endian);
	if (window && window->depth)
		free(window->depth);
	if (window && window->img_data)
		free(window->img_data);
	if (window)
		free(window);
}

int             key_press(int key, t_window *window)
{
	(key == 53) ? close_window(window) : 0;
	return (0);
}

/*int             mouse_buttons(int key, int x, int y, t_window *window)
{
	if (key == 4 || key == 5)
	{
		zoom_fix(x, y, key, window);
		ft_bzero(window->img_data,  MAP_W * UNIQ_BPP * MAP_H);
		clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &work_size, NULL, 0, NULL, NULL);
//		test_mandel(window);
		draw_thing(window);
	}
	return (0);
}*/

/*void		zoom_fix(int x, int y, int key, t_window *window)
{

	window->x_fix = MAP_W / 2 - x;
	window->y_fix = MAP_H / 2 - y;
	if (key == 4)
		window->zoom_fix += 0.1;
	else
	{
		if (window->zoom_fix > 0.2)
			window->zoom_fix -= 0.1;
	}

}*/