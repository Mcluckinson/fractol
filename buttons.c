/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:26:15 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/19 20:27:15 by cyuriko          ###   ########.fr       */
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
