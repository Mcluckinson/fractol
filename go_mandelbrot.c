/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:10:15 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 22:48:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_params_mandelbrot(t_graphon *graf, t_fract *fract)
{
	graf->ret = clSetKernelArg(graf->kernel, 0, sizeof(double), &fract->min_re);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 1, sizeof(double), &fract->max_re);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 2, sizeof(double), &fract->min_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 3, sizeof(double), &fract->max_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 4,
			sizeof(double), &fract->factor_re);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 5,
			sizeof(double), &fract->factor_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 6, sizeof(int), &fract->map_w);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 7,
			sizeof(cl_mem), &graf->img_data);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 8,
			sizeof(int), &fract->max_iteration);
	error(graf->ret);
}

static void		run_mandelbrot(t_graphon *graphon, t_window *window)
{
	graphon->work_size = MAP_W * MAP_H;
	graphon->ret = clEnqueueNDRangeKernel(graphon->command_queue,
			graphon->kernel, 1, NULL, &graphon->work_size, NULL, 0, NULL, NULL);
	error(graphon->ret);
	graphon->ret = clEnqueueReadBuffer(graphon->command_queue,
			graphon->img_data, CL_TRUE, 0,
			sizeof(char) * MAP_H * MAP_W * UNIQ_BPP, window->img_data,
			0, NULL, NULL);
	error(graphon->ret);
	mlx_put_image_to_window(window->mlx_ptr,
			window->win_ptr, window->img_ptr, 0, 0);
}

void			go_mandelbrot(t_window *win, t_graphon *graphon, t_fract *frac)
{
	graphon->program_string = read_file(
			"/Users/cyuriko/fractol_to_git/fract_codes/mandelbrot.cl");
	graphon->program_len = ft_strlen(graphon->program_string);
	graphon->program = clCreateProgramWithSource(graphon->context, 1,
			(const char**)&graphon->program_string,
			&graphon->program_len, &graphon->ret);
	error(graphon->ret);
	graphon->ret = clBuildProgram(graphon->program,
			1, &graphon->device_id, NULL, NULL, NULL);
	error_log(graphon);
	error(graphon->ret);
	graphon->kernel = clCreateKernel(graphon->program, "test", &graphon->ret);
	error(graphon->ret);
	graphon->img_data = clCreateBuffer(graphon->context,
			CL_MEM_READ_WRITE, MAP_W * MAP_H * UNIQ_BPP * sizeof(char),
			NULL, &graphon->ret);
	error(graphon->ret);
	init_params_mandelbrot(graphon, frac);
	run_mandelbrot(graphon, win);
}

void			draw_mandelbrot(t_graphon *graf, t_fract *frac, t_window *win)
{
	init_params_mandelbrot(graf, frac);
	run_mandelbrot(graf, win);
}
