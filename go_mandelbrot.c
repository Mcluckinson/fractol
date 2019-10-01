/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:10:15 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/01 17:37:00 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_params_mandelbrot(t_graphon *graphon/*, t_window *window*/, t_fractol *fractol)
{
	////////////ЗДЕСЬ БУДУТ АРГУМЕНТЫ
	//////////////ДАБЛЫ С РАСЧЕТАМИ ДЛЯ ФРАКТАЛА
/*	double min_re = -4.6;/////////min_re
	double max_re = 3.7;////////max_re
	double min_im = -2.0;////////min_im
	double max_im = min_im + (max_re - min_re) * ((double) (MAP_H) / ((double) MAP_W));////////max_im
	double factor_re = (max_re - min_re) / (MAP_W - 1);////////factor_re/////////ЭТО ЗУМ БЛЯ
	double factor_im = (max_im - min_im) / (MAP_H - 1);////////factor_im/////////И ЭТО
	graphon->ret = clSetKernelArg(graphon->kernel, 0, sizeof(double), &min_re);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 1, sizeof(double), &max_re);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 2, sizeof(double), &min_im);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 3, sizeof(double), &max_im);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 4, sizeof(double), &factor_re);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 5, sizeof(double), &factor_im);
	error(graphon->ret);*/
	/////////////ЗАКОНЧИЛОСЬ ПРО ДАБЛЫ ЕБАТЬ ПереДАЕМ МАП_В
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

	graphon->ret = clSetKernelArg(graphon->kernel, 6, sizeof(int), &map_w);/////////////кернел аргумент 0
	error(graphon->ret);

	///////////////
	graphon->ret = clSetKernelArg(graphon->kernel, 7, sizeof(cl_mem), &graphon->img_data);/////////////кернел аргумент 0
	error(graphon->ret);

	//////////////ВСЕ АРГУМЕНТЫ ЗАКОНЧИЛИСЬ
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
}

void	go_mandelbrot(t_window *window, t_graphon *graphon, t_fractol *fractol)
{
//	graphon->ret = clGetPlatformIDs(1, &graphon->platform_id, &graphon->num_platforms);///////////получаем платформы
//	error(graphon->ret);
//	graphon->ret = clGetDeviceIDs(graphon->platform_id, CL_DEVICE_TYPE_GPU, 1, &graphon->device_id, &graphon->num_devices); /////////девайс айди для видюхи
//	error(graphon->ret);
//	graphon->context = clCreateContext(NULL, 1, &graphon->device_id, NULL, NULL, &graphon->ret);/////////ебучий контекст
//	error(graphon->ret);
//	graphon->command_queue = clCreateCommandQueue(graphon->context, graphon->device_id, 0, &graphon->ret);//////////очередь команд бля
//	error(graphon->ret);
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
	init_params_mandelbrot(graphon/*, window*/, fractol);
	run_mandelbrot(graphon, window/*, fractol*/);
}
