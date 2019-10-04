/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:45:30 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 22:56:53 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	start_cl(t_graphon *graphon)
{
	graphon->ret = clGetPlatformIDs(1, &graphon->platform_id,
			&graphon->num_platforms);
	error(graphon->ret);
	graphon->ret = clGetDeviceIDs(graphon->platform_id,
			CL_DEVICE_TYPE_GPU, 1, &graphon->device_id, &graphon->num_devices);
	error(graphon->ret);
	graphon->context = clCreateContext(NULL, 1,
			&graphon->device_id, NULL, NULL, &graphon->ret);
	error(graphon->ret);
	graphon->command_queue = clCreateCommandQueue(graphon->context,
			graphon->device_id, 0, &graphon->ret);
	error(graphon->ret);
}
