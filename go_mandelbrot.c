/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:10:15 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 12:42:55 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_params_mandelbrot(t_graphon *graphon, t_fractol *fractol)
{
	graphon->ret = clSetKernelArg(graphon->kernel, 0, sizeof(double), &fractol->min_re);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 1, sizeof(double), &fractol->max_re);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 2, sizeof(double), &fractol->min_im);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 3, sizeof(double), &fractol->max_im);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 4, sizeof(double), &fractol->factor_re);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 5, sizeof(double), &fractol->factor_im);
	error(graphon->ret);
	int map_w = MAP_W;
	graphon->ret = clSetKernelArg(graphon->kernel, 6, sizeof(int), &map_w);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 7, sizeof(cl_mem), &graphon->img_data);
	error(graphon->ret);
}

static void		run_mandelbrot(t_graphon *graphon, t_window *window)
{
	graphon->work_size = MAP_W * MAP_H;/////////////количество запусков
	graphon->ret = clEnqueueNDRangeKernel(graphon->command_queue, graphon->kernel, 1, NULL, &graphon->work_size, NULL,
										  0, NULL, NULL);///////////////запускаем кернел
	error(graphon->ret);
	char *my_image = malloc(sizeof(char) * MAP_H * MAP_W * 4);///////////БУФЕР ЧТОБЫ ДОСТАТЬ В НЕГО ДАННЫЕ ИЗ ВИДЕОКАРТЫ
	graphon->ret = clEnqueueReadBuffer(graphon->command_queue, graphon->img_data, CL_TRUE, 0,
									   sizeof(char) * MAP_H * MAP_W * UNIQ_BPP, my_image, 0, NULL,
									   NULL);////////////ЧИТАЕМ В БУФЕР ИЗ ВИДЕОКАРТЫ
	error(graphon->ret);
	ft_memcpy(window->img_data, my_image, MAP_W * MAP_H * UNIQ_BPP);//////////КОПИРУЕМ БУФЕР В МЛХ
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);//////////КИДАЕМ ЭТУ ХУЙНЮ В ОКНО
	free(my_image);
	free(graphon->program_string);
}

void	go_mandelbrot(t_window *window, t_graphon *graphon, t_fractol *fractol)
{

	graphon->program_string = read_file(
			"/Users/cyuriko/fractol_to_git/fract_codes/mandelbrot.cl");////////////читаем файл с кернелом в програм стринг
	graphon->program_len = ft_strlen(graphon->program_string);//////////длина програм стринг окей
	graphon->program = clCreateProgramWithSource(graphon->context, 1, (const char **) &graphon->program_string,
												 &graphon->program_len, &graphon->ret);///////////создаем программу
	error(graphon->ret);
	graphon->ret = clBuildProgram(graphon->program, 1, &graphon->device_id, NULL, NULL,
								  NULL);////////////////создаем программу - 2
	error_log(graphon);
	error(graphon->ret);
	graphon->kernel = clCreateKernel(graphon->program, "test", &graphon->ret);///////////создаем кернел
	error(graphon->ret);
	graphon->img_data = clCreateBuffer(graphon->context, CL_MEM_READ_WRITE, MAP_W * MAP_H * UNIQ_BPP * sizeof(char),
									   NULL, &graphon->ret);/////////////буфер в видеокарте
	error(graphon->ret);
	init_params_mandelbrot(graphon, fractol);
	run_mandelbrot(graphon, window);
}

void	draw_mandelbrot(t_graphon *graphon, t_fractol *fractol, t_window *window)
{
	init_params_mandelbrot(graphon, fractol);
	run_mandelbrot(graphon, window);
}