/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:45:30 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/30 13:25:07 by cyuriko          ###   ########.fr       */
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
	graphon->ret = clGetPlatformIDs(1, &graphon->platform_id, &graphon->num_platforms);
	error(graphon->ret);
	graphon->ret = clGetDeviceIDs(graphon->platform_id, CL_DEVICE_TYPE_GPU, 1, &graphon->device_id, &graphon->num_devices);
	error(graphon->ret);
	graphon->context = clCreateContext(NULL, 1, &graphon->device_id, NULL, NULL, &graphon->ret);
	error(graphon->ret);
	graphon->command_queue = clCreateCommandQueue(graphon->context, graphon->device_id, 0, &graphon->ret);
	error(graphon->ret);
	graphon->program_string = read_file("/Users/cyuriko/fractol_to_git/test.cl");
	graphon->program_len = ft_strlen(graphon->program_string);
	graphon->program = clCreateProgramWithSource(graphon->context, 1, (const char**)&graphon->program_string, &graphon->program_len, &graphon->ret);
	error(graphon->ret);
	graphon->ret = clBuildProgram(graphon->program, 1, &graphon->device_id, NULL, NULL, NULL);
	error_log(graphon);
	error(graphon->ret);
	graphon->kernel = clCreateKernel(graphon->program, "test", &graphon->ret);
	error(graphon->ret);
	graphon->img_data = clCreateBuffer(graphon->context, CL_MEM_READ_WRITE, MAP_W * MAP_H * UNIQ_BPP * sizeof(char), NULL, &graphon->ret);
	error(graphon->ret);
	graphon->ret = clSetKernelArg(graphon->kernel, 0, sizeof(cl_mem), &graphon->img_data);
	error(graphon->ret);

	graphon->work_size = MAP_W * MAP_H;
	graphon->ret = clEnqueueNDRangeKernel(graphon->command_queue, graphon->kernel, 1, NULL, &graphon->work_size, NULL, 0, NULL, NULL);
	error(graphon->ret);
	int *my_image = malloc(sizeof(int) * MAP_H * MAP_W);
	graphon->ret = clEnqueueReadBuffer(graphon->command_queue, graphon->img_data, CL_TRUE, 0, sizeof(int) * MAP_H * MAP_W, my_image, 0, NULL, NULL);
	error(graphon->ret);
	printf("Start drawing!\n");
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, x, y, my_image[x + y * MAP_W]);
		}
	}
//	graphon->ret = clEnqueueReadBuffer(graphon->command_queue, graphon->img_data, CL_TRUE, 0, sizeof(char) * MAP_H * MAP_W * UNIQ_BPP, window->img_data, 0, NULL, NULL);
//	error(graphon->ret);
}

/*void	go_cl(t_graphon *graphon)
{
	graphon->ret = clEnqueueNDRangeKernel(graphon->command_queue, graphon->kernel, 1, NULL, &graphon->work_size, NULL, 0, NULL, NULL);
	error(graphon->ret);
}*/