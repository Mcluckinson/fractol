/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:00:07 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 14:10:48 by cyuriko          ###   ########.fr       */
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
	if (key == 53)
		close_window(window);
	if (key > 122 && key < 127)
	{
		arrow_fix(key, window->fractol);
		ft_bzero(window->img_data, MAP_W * UNIQ_BPP * MAP_H);
		rangers_assemble(window, window->graphon, window->fractol);
	}

	return (0);
}

int             mouse_buttons(int key, int x, int y, t_window *window)
{
	if (key == 4 || key == 5)
	{
		zoom_fix(key, window->fractol, x, y);
		ft_bzero(window->img_data,  MAP_W * UNIQ_BPP * MAP_H);
		rangers_assemble(window, window->graphon, window->fractol);
	}
	return (0);
}

void		fix_iterations(int key, t_window *window)
{

}