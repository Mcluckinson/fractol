/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:41:57 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/01 17:33:07 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_window		*init_window()
{
	t_window *window;
	window = (t_window*)malloc(sizeof(t_window));
	/////защитить
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, MAP_W, MAP_H, "test");////название карты конечно же
	window->img_ptr = mlx_new_image(window->mlx_ptr, MAP_W, MAP_H);
	/////короче ща пока замаллочу это говно а там видно будет похер
	window->linesize = (int*)malloc(sizeof(int));
	window->endian = (int*)malloc(sizeof(int));
	window->depth = (int*)malloc(sizeof(int));
	///////вот замаллочил ну там глянь потом Илюха может чо получше придумаешь, а нет, так защитить не забудь это говно
	*window->endian = 0;
	*window->linesize = UNIQ_BPP * MAP_W;
	*window->depth = UNIQ_BPP * 8;
//	window->max_iteration = 50;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth,
										 window->linesize, window->endian);
//	window->zoom_fix = 1;
//	window->x_fix = 0;
//	window->y_fix = 0;
	return (window);
}

t_fractol		*init_data()
{
	t_fractol	*fractol;
	if (!(fractol = (t_fractol*)ft_memalloc(sizeof(t_fractol))))
		return (NULL);
	fractol->min_re = -4.6;
	fractol->max_re = 3.7;
	fractol->min_im = -2.0;
	fractol->max_im = fractol->min_im + (fractol->max_re - fractol->min_re) * ((double)(MAP_H) / ((double)MAP_W));
	fractol->factor_re = (fractol->max_re - fractol->min_re) / (MAP_W - 1);////////factor_re/////////ЭТО ЗУМ БЛЯ
	fractol->factor_im = (fractol->max_im - fractol->min_im) / (MAP_H - 1);////////factor_im/////////И ЭТО
	fractol->k_re = -0.4;
	fractol->k_im = 0.6;
	return (fractol);
}