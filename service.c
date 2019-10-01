/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:49 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/01 15:51:38 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void 	error(int ret)
{
	if (ret != CL_SUCCESS)
		exit(ret);
	return ;
}

char *read_file(char *path)///////ЭТОЙ ХУЙНЕЙ ПОЛЬЗОВАТЬСЯ НЕЛЬЗЯ БЛЯДЬ АККУРАТНО НУ ЭТО КОНЕЧНО ДЛЯ БОНУСА НО ТЫ ТАМ СМОТРИ ЕБАТЬ
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

void	error_log(t_graphon *graphon)
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
