/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:41:57 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/05 00:30:53 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_window		*init_window(void)
{
	t_window *window;

	if (!(window = (t_window*)malloc(sizeof(t_window))))
		return (NULL);
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, MAP_W, MAP_H, "FRACTOL");
	window->img_ptr = mlx_new_image(window->mlx_ptr, MAP_W, MAP_H);
	window->endian = 0;
	window->linesize = UNIQ_BPP * MAP_W;
	window->depth = UNIQ_BPP * 8;
	window->img_data = mlx_get_data_addr(window->img_ptr,
			&window->depth, &window->linesize, &window->endian);
	return (window);
}

t_fract			*init_data(void)
{
	t_fract	*fractol;

	if (!(fractol = (t_fract*)ft_memalloc(sizeof(t_fract))))
		return (NULL);
	fractol->min_re = -2.0;
	fractol->max_re = 2.0;
	fractol->min_im = -2.0;
	fractol->max_im = fractol->min_im +
			(fractol->max_re - fractol->min_re) *
			((double)(MAP_H) / ((double)MAP_W));
	fractol->factor_re = (fractol->max_re - fractol->min_re) / (MAP_W - 1);
	fractol->factor_im = (fractol->max_im - fractol->min_im) / (MAP_H - 1);
	fractol->k_re = 0.368;
	fractol->k_im = -0.203;
	fractol->max_iteration = 20;
	fractol->thingy_block = 0;
	fractol->map_w = MAP_W;
	return (fractol);
}
