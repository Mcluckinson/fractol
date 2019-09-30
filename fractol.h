/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:09:34 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/29 17:33:34 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <pthread.h>
# include <OpenCL/opencl.h>
# define UNIQ_BPP 4
# define MAP_H 1000
# define MAP_W 2000

typedef	struct 		s_graphon
{
	int 				ret;
	cl_platform_id		platform_id;
	cl_uint				num_platforms;
	cl_device_id		device_id; ////это будет айди видюхи
	cl_uint				num_devices;
	cl_context 			context;
	cl_command_queue	command_queue;
	char 				*program_string;
	size_t 				program_len;
	cl_program 			program;
	cl_kernel 			kernel;
	size_t 				work_size;
	cl_mem				img_data;
}					t_graphon;

typedef struct 		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char 			*img_data;
	int				*endian;
	int				*linesize;
	int				*depth;
	int				iteration;
	double			max_iteration;
	float 			zoom_fix;
	int 			x_fix;
	int 			y_fix;
	int 			real_x;
	int 			real_y;
}					t_window;

typedef struct 		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct 		s_params
{

}					t_params;

//void	get_color(int iteration, int i, t_window *window);
//void	put_point(int x, int y, t_window *window, int iteration);
//void			test_mandel(t_window *window);
t_complex init_complex(double re, double im);
t_window		*init_window();
void	draw_thing(t_window *window);
int             close_window(t_window *window);
void			del_win(t_window *window);
int             key_press(int key, t_window *window);
//void		zoom_fix(int x, int y, int key, t_window *window);
//int             mouse_buttons(int key, int x, int y, t_window *window);
void	start_cl(t_graphon *graphon, t_window *window);
//void	go_cl(t_graphon *graphon);

#endif