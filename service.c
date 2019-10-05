/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:49:49 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/05 16:25:31 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	del_win(t_window *window)
{
	if (window && window->fractol)
		free(window->fractol);
	if (window && window->win_ptr)
		free(window->win_ptr);
	if (window && window->mlx_ptr)
		free(window->mlx_ptr);
	if (window && window->img_ptr)
		free(window->img_ptr);
	if (window && window->img_data)
		free(window->img_data);
	if (window)
		free(window);
}

void	error(int ret)
{
	if (ret != CL_SUCCESS)
		exit(ret);
	return ;
}

char	*read_file(char *path)
{
	char	*buffer;
	char	buffer_temp[5000];
	int		fd;

	buffer = NULL;
	fd = open(path, O_RDONLY);
	if (!fd)
		return (NULL);
	if (read(fd, buffer_temp, 5000))
		buffer = strdup(buffer_temp);
	close(fd);
	return (buffer);
}

void	error_log(t_graphon *graphon)
{
	char	*log;
	size_t	log_size;

	if (graphon->ret != CL_SUCCESS)
	{
		clGetProgramBuildInfo(graphon->program, graphon->device_id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = ft_memalloc((log_size + 1) * sizeof(char));
		if (!log)
			exit(graphon->ret);
		clGetProgramBuildInfo(graphon->program,
				graphon->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putstr_fd(log, 2);
		free(log);
	}
}

int		julia_thingy(int x, int y, t_window *window)
{
	if (window->fractol->thingy_block == 0)
	{
		window->fractol->k_re = ((double)x / MAP_W - 0.5);
		window->fractol->k_im = ((double)(MAP_H - y) / MAP_H - 0.5);
		draw_julia(window->graphon, window->fractol, window);
	}
	return (0);
}
