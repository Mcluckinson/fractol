/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:45:30 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/30 21:02:10 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void 	error(int ret)
{
	if (ret != CL_SUCCESS)
		exit(ret);
	return ;
}

static	void	error_log(t_graphon *graphon)
{
	if (graphon->ret != CL_SUCCESS)//////эта хуйня выведет ошибку если в кернеле написано говно, попробуй написать хуйню в тест.сл
	{
		size_t log_size;
		clGetProgramBuildInfo(graphon->program, graphon->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *log = ft_memalloc((log_size + 1) * sizeof(char));
		if (!log)
			exit(graphon->ret) ;
		clGetProgramBuildInfo(graphon->program, graphon->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putstr_fd(log, 2);
	}
}

static	char *read_file(char *path)///////ЭТОЙ ХУЙНЕЙ ПОЛЬЗОВАТЬСЯ НЕЛЬЗЯ БЛЯДЬ АККУРАТНО НУ ЭТО КОНЕЧНО ДЛЯ БОНУСА НО ТЫ ТАМ СМОТРИ ЕБАТЬ
{
	char *buffer = 0;
	long length;
	FILE * f = fopen (path, "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = ft_strnew(length);/////не забудь это зафришить
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose (f);
	}
	return (buffer);
}

void	start_cl(t_graphon *graphon, t_window *window)
{
	graphon->ret = clGetPlatformIDs(1, &graphon->platform_id, &graphon->num_platforms);///////////получаем платформы
	error(graphon->ret);
	graphon->ret = clGetDeviceIDs(graphon->platform_id, CL_DEVICE_TYPE_GPU, 1, &graphon->device_id, &graphon->num_devices); /////////девайс айди для видюхи
	error(graphon->ret);
	graphon->context = clCreateContext(NULL, 1, &graphon->device_id, NULL, NULL, &graphon->ret);/////////ебучий контекст
	error(graphon->ret);
	graphon->command_queue = clCreateCommandQueue(graphon->context, graphon->device_id, 0, &graphon->ret);//////////очередь команд бля
	error(graphon->ret);
	graphon->program_string = read_file("/Users/cyuriko/fractol_to_git/test.cl");////////////читаем файл с кернелом в програм стринг
	graphon->program_len = ft_strlen(graphon->program_string);//////////длина програм стринг окей
	graphon->program = clCreateProgramWithSource(graphon->context, 1, (const char**)&graphon->program_string, &graphon->program_len, &graphon->ret);///////////создаем программу
	error(graphon->ret);
	graphon->ret = clBuildProgram(graphon->program, 1, &graphon->device_id, NULL, NULL, NULL);////////////////создаем программу - 2
	error_log(graphon);
	error(graphon->ret);
	graphon->kernel = clCreateKernel(graphon->program, "test", &graphon->ret);///////////создаем кернел
	error(graphon->ret);
	graphon->img_data = clCreateBuffer(graphon->context, CL_MEM_READ_WRITE, MAP_W * MAP_H * UNIQ_BPP * sizeof(char), NULL, &graphon->ret);/////////////буфер в видеокарте
	error(graphon->ret);

	////////////ЗДЕСЬ БУДУТ АРГУМЕНТЫ

//	int map_h = MAP_H;






	//////////////МАССИВ ДАБЛОВ С РАСЧЕТАМИ ДЛЯ ФРАКТАЛА
	double min_re = -3.6;/////////min_re
	double max_re = 3.7;////////max_re
	double min_im = -3.0;////////min_im
	double	max_im = min_im + (max_re - min_re) * ((double)(MAP_H) / ((double)MAP_W));////////max_im
	double factor_re = (max_re - min_re) / (MAP_W / 2 - 1);////////factor_re/////////ЭТО ЗУМ БЛЯ
	double factor_im = (max_im - min_im) / (MAP_H / 2 - 1);////////factor_im/////////И ЭТО
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
	error(graphon->ret);
	/////////////ЗАКОНЧИЛОСЬ ПРО МАССИВ ЕБАТЬ ПереДАЕМ МАП_В
	int map_w = MAP_W;

	graphon->ret = clSetKernelArg(graphon->kernel, 6, sizeof(int), &map_w);/////////////кернел аргумент 0
	error(graphon->ret);

	///////////////
	graphon->ret = clSetKernelArg(graphon->kernel, 7, sizeof(cl_mem), &graphon->img_data);/////////////кернел аргумент 0
	error(graphon->ret);

	//////////////ВСЕ АРГУМЕНТЫ ЗАКОНЧИЛИСЬ
	graphon->work_size = MAP_W * MAP_H;/////////////количество запусков
	graphon->ret = clEnqueueNDRangeKernel(graphon->command_queue, graphon->kernel, 1, NULL, &graphon->work_size, NULL, 0, NULL, NULL);///////////////запускаем кернел
	error(graphon->ret);
	char *my_image = malloc(sizeof(char) * MAP_H * MAP_W * 4);///////////БУФЕР ЧТОБЫ ДОСТАТЬ В НЕГО ДАННЫЕ ИЗ ВИДЕОКАРТЫ
	graphon->ret = clEnqueueReadBuffer(graphon->command_queue, graphon->img_data, CL_TRUE, 0, sizeof(char) * MAP_H * MAP_W * UNIQ_BPP, my_image, 0, NULL, NULL);////////////ЧИТАЕМ В БУФЕР ИЗ ВИДЕОКАРТЫ
	error(graphon->ret);
	ft_memcpy(window->img_data, my_image, MAP_W * MAP_H * UNIQ_BPP);//////////КОПИРУЕМ БУФЕР В МЛХ
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);//////////КИДАЕМ ЭТУ ХУЙНЮ В ОКНО
	free(my_image);
}

/*void	go_cl(t_graphon *graphon)
{
	graphon->ret = clEnqueueNDRangeKernel(graphon->command_queue, graphon->kernel, 1, NULL, &graphon->work_size, NULL, 0, NULL, NULL);
	error(graphon->ret);
}*/