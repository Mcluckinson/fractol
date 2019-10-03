/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:59:19 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/03 19:10:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void go_left(t_fractol *fractol)
{
	fractol->max_re+= 0.1;
	fractol->min_re+= 0.1;
}

static void go_right(t_fractol *fractol)
{
	fractol->max_re-= 0.1;
	fractol->min_re-= 0.1;
}
static void go_down(t_fractol *fractol)
{
	fractol->max_im += 0.1;
	fractol->min_im += 0.1;
}
static void go_up(t_fractol *fractol)
{
	fractol->max_im -= 0.1;
	fractol->min_im -= 0.1;
}
void arrow_fix(int key, t_fractol *fractol)
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