/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:04:28 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 22:58:55 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_in(int x, int y, t_fract *fractol)
{
	double k_re;
	double k_im;

	k_re = x * (fractol->max_re - fractol->min_re) / MAP_W + fractol->min_re;
	k_im = y * (fractol->max_im - fractol->min_im) / MAP_H + fractol->min_im;
	fractol->max_re = k_re + (fractol->max_re - k_re) * 1.1;
	fractol->max_im = k_im + (fractol->max_im - k_im) * 1.1;
	fractol->min_re = k_re + (fractol->min_re - k_re) * 1.1;
	fractol->min_im = k_im + (fractol->min_im - k_im) * 1.1;
	fractol->factor_re = (fractol->max_re - fractol->min_re) / MAP_W;
	fractol->factor_im = (fractol->max_im - fractol->min_im) / MAP_H;
}

static void	zoom_out(int x, int y, t_fract *fractol)
{
	double k_re;
	double k_im;

	k_re = x * (fractol->max_re - fractol->min_re) / MAP_W + fractol->min_re;
	k_im = y * (fractol->max_im - fractol->min_im) / MAP_H + fractol->min_im;
	fractol->max_re = k_re + (fractol->max_re - k_re) / 1.1;
	fractol->max_im = k_im + (fractol->max_im - k_im) / 1.1;
	fractol->min_re = k_re + (fractol->min_re - k_re) / 1.1;
	fractol->min_im = k_im + (fractol->min_im - k_im) / 1.1;
	fractol->factor_re = (fractol->max_re - fractol->min_re) / MAP_W;
	fractol->factor_im = (fractol->max_im - fractol->min_im) / MAP_H;
}

void		zoom_fix(int key, t_fract *fractol, int x, int y)
{
	if (key == 4)
		zoom_in(x, y, fractol);
	else if (key == 5)
		zoom_out(x, y, fractol);
	return ;
}
