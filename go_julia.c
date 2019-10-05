/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:07:48 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 22:19:28 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		params_julia_2(t_graphon *graf, t_fract *frac)
{
	graf->ret = clSetKernelArg(graf->kernel, 5,
			sizeof(double), &frac->factor_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 6, sizeof(int), &frac->map_w);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 7,
			sizeof(cl_mem), &graf->img_data);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 8, sizeof(double), &frac->k_re);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 9, sizeof(double), &frac->k_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 10,
			sizeof(int), &frac->max_iteration);
	error(graf->ret);
}

static void		init_params_julia(t_graphon *graf, t_fract *frac)
{
	graf->ret = clSetKernelArg(graf->kernel, 0, sizeof(double), &frac->min_re);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 1, sizeof(double), &frac->max_re);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 2, sizeof(double), &frac->min_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 3, sizeof(double), &frac->max_im);
	error(graf->ret);
	graf->ret = clSetKernelArg(graf->kernel, 4,
			sizeof(double), &frac->factor_re);
	error(graf->ret);
	params_julia_2(graf, frac);
}

static void		run_julia(t_graphon *graf, t_window *window)
{
	graf->work_size = MAP_W * MAP_H;
	graf->ret = clEnqueueNDRangeKernel(graf->command_queue,
			graf->kernel, 1, NULL, &graf->work_size, NULL, 0, NULL, NULL);
	error(graf->ret);
	graf->ret = clEnqueueReadBuffer(graf->command_queue,
			graf->img_data, CL_TRUE, 0, sizeof(char) * MAP_H * MAP_W * UNIQ_BPP,
			window->img_data, 0, NULL, NULL);
	error(graf->ret);
	mlx_put_image_to_window(window->mlx_ptr,
			window->win_ptr, window->img_ptr, 0, 0);
}

void			go_julia(t_window *window, t_graphon *graphon, t_fract *fractol)
{
	graphon->program_string = read_file(
			"./fract_codes/julia.cl");
	graphon->program_len = ft_strlen(graphon->program_string);
	graphon->program = clCreateProgramWithSource(graphon->context, 1,
			(const char**)&graphon->program_string,
			&graphon->program_len, &graphon->ret);
	error(graphon->ret);
	graphon->ret = clBuildProgram(graphon->program, 1,
			&graphon->device_id, NULL, NULL, NULL);
	error_log(graphon);
	error(graphon->ret);
	graphon->kernel = clCreateKernel(graphon->program, "test", &graphon->ret);
	error(graphon->ret);
	graphon->img_data = clCreateBuffer(graphon->context, CL_MEM_READ_WRITE,
			MAP_W * MAP_H * UNIQ_BPP * sizeof(char), NULL, &graphon->ret);
	error(graphon->ret);
	init_params_julia(graphon, fractol);
	run_julia(graphon, window);
}

void			draw_julia(t_graphon *graphon,
		t_fract *fractol, t_window *window)
{
	init_params_julia(graphon, fractol);
	run_julia(graphon, window);
}
