/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:59:19 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 21:44:06 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	go_left(t_fract *fractol)
{
	fractol->max_re += fractol->factor_re * 2;
	fractol->min_re += fractol->factor_re * 2;
}

static void	go_right(t_fract *fractol)
{
	fractol->max_re -= fractol->factor_re * 2;
	fractol->min_re -= fractol->factor_re * 2;
}

static void	go_down(t_fract *fractol)
{
	fractol->max_im += fractol->factor_im * 2;
	fractol->min_im += fractol->factor_im * 2;
}

static void	go_up(t_fract *fractol)
{
	fractol->max_im -= fractol->factor_im * 2;
	fractol->min_im -= fractol->factor_im * 2;
}

void		arrow_fix(int key, t_fract *fractol)
{
	if (key == 126)
		go_up(fractol);
	if (key == 125)
		go_down(fractol);
	if (key == 123)
		go_left(fractol);
	if (key == 124)
		go_right(fractol);
}
