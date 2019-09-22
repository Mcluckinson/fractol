/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:09:34 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/22 17:13:28 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>
# define UNIQ_BPP 4
# define MAP_H 1000
# define MAP_W 2000

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
}					t_window;

typedef struct 		s_complex
{
	double			re;
	double			im;
}					t_complex;

void	get_color(int iteration, int i, t_window *window);
void	put_point(int x, int y, t_window *window, int iteration);
void			test_mandel(t_window *window);
t_complex init_complex(double re, double im);
t_window		*init_window();
void	draw_thing(t_window *window);
int             close_window(t_window *window);
void			del_win(t_window *window);
int             key_press(int key, t_window *window);


#endif