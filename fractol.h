/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:09:34 by cyuriko           #+#    #+#             */
/*   Updated: 2019/10/04 22:19:12 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <OpenCL/opencl.h>
# define UNIQ_BPP 4
# define MAP_H 1000
# define MAP_W 1000

typedef	struct			s_graphon
{
	int					ret;
	cl_platform_id		platform_id;
	cl_uint				num_platforms;
	cl_device_id		device_id;
	cl_uint				num_devices;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*program_string;
	size_t				program_len;
	cl_program			program;
	cl_kernel			kernel;
	size_t				work_size;
	cl_mem				img_data;
}						t_graphon;

typedef struct			s_fract
{
	double				min_re;
	double				max_re;
	double				min_im;
	double				max_im;
	double				factor_re;
	double				factor_im;
	double				k_re;
	double				k_im;
	char				*name;
	int					max_iteration;
	int					thingy_block;
	int					map_w;
}						t_fract;

typedef struct			s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_data;
	int					endian;
	int					linesize;
	int					depth;
	t_fract				*fractol;
	t_graphon			*graphon;
}						t_window;

t_window				*init_window();
int						close_window(t_window *window);
void					del_win(t_window *window);
int						key_press(int key, t_window *window);
int						mouse_buttons(int key, int x, int y, t_window *window);
void					start_cl(t_graphon *graphon);
void					error(int ret);
char					*read_file(char *path);
t_fract					*init_data();
void					error_log(t_graphon *graphon);
void					go_mandelbrot(t_window *window,
		t_graphon *graphon, t_fract *fractol);
void					go_mandelbar(t_window *window,
		t_graphon *graphon, t_fract *fractol);
void					go_julia(t_window *window,
		t_graphon *graphon, t_fract *fractol);
void					go_ship(t_window *window,
		t_graphon *graphon, t_fract *fractol);
void					zoom_fix(int key, t_fract *fractol,
		int x, int y);
void					go_go(t_window *window,
		char *name, t_graphon *graphon, t_fract *fractol);
void					arrow_fix(int key, t_fract *fractol);
void					draw_mandelbar(t_graphon *graphon,
		t_fract *fractol, t_window *window);
void					draw_julia(t_graphon *graphon,
		t_fract *fractol, t_window *window);
void					draw_ship(t_graphon *graphon,
		t_fract *fractol, t_window *window);
void					draw_mandelbrot(t_graphon *graphon,
		t_fract *fractol, t_window *window);
void					rangers_assemble(t_window *window,
		t_graphon *graphon, t_fract *fractol);
int						julia_thingy(int x, int y, t_window *window);
void					fix_iterations(int key, t_window *window);

#endif
