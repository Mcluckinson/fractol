#include "fractol.h"

t_window		*init_window()
{
	t_window *window;
	window = (t_window*)malloc(sizeof(t_window));
	/////защитить
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, MAP_W, MAP_H, "test");////название карты конечно же
	window->img_ptr = mlx_new_image(window->mlx_ptr, MAP_W, MAP_H);
	/////короче ща пока замаллочу это говно а там видно будет похер
	window->linesize = (int*)malloc(sizeof(int));
	window->endian = (int*)malloc(sizeof(int));
	window->depth = (int*)malloc(sizeof(int));
	///////вот замаллочил ну там глянь потом Илюха может чо получше придумаешь, а нет, так защитить не забудь это говно
	*window->endian = 0;
	*window->linesize = UNIQ_BPP * MAP_W;
	*window->depth = UNIQ_BPP * 8;
	window->max_iteration = 50;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth,
										 window->linesize, window->endian);
	window->zoom_fix = 1;
	window->x_fix = 0;
	window->y_fix = 0;
	return (window);
}

t_complex init_complex(double re, double im)
{
	t_complex complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

/*void			test_mandel(t_window *window)
{
	t_complex	z;
	double	min_re = -3.6;
	double	max_re = 3.7;
	double	min_im = -2.0;
	double	max_im = min_im + (max_re - min_re) * ((double)(MAP_H) / ((double)MAP_W));
//	double	iteration;
	int		iteration;
	int		y;
	y = 0;
	double	factor_re = (max_re - min_re) / (MAP_W - 1);
	double	factor_im = (max_im - min_im) / (MAP_H - 1);
	int x;
	double	c_re;
	double	c_im;

	while (y < MAP_H)
	{
		window->real_y = (y - window->y_fix) * window->zoom_fix;
		c_im = max_im - y * factor_im;
		x = 0;
		while (x < MAP_W)
		{
			window->real_x = (x - window->x_fix) * window->zoom_fix;
			c_re = min_re + x * factor_re;
			z = init_complex(c_re, c_im);
			iteration = 0;
			while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
				   && iteration < window->max_iteration)
			{
				z = init_complex(
						pow(z.re, 2.0) - pow(z.im, 2.0) + c_re,
						2.0 * z.re * z.im + c_im);
				iteration++;
			}// Формула множества Мандельброта
			if (window->real_x > 0 && window->real_x < MAP_W && window->real_y > 0 && window->real_y < MAP_H)
				put_point(window->real_x, window->real_y, window, iteration);// Установка цвета точки
			x++;
		}
		y++;
	}
}*/

/*void	put_point(int x, int y, t_window *window, int iteration)
{
	int i;
	i = (y * *window->linesize) + x * UNIQ_BPP;
	get_color(iteration, i, window);
}

void	get_color(int iteration, int i, t_window *window)
{
	double t;
	unsigned int	red;
	unsigned int	blue;
	unsigned int	green;

	t = (double)iteration / window->max_iteration;
	red = (int)(9 * (1 - t) * pow(t, 3) * 255);
	green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	window->img_data[i] = blue;
	window->img_data[++i] = green;
	window->img_data[++i] = red;
}*/

void	draw_thing(t_window *window)
{
mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);
}

//# define CHECK_ERROR { if (ret != CL_SUCCESS) exit(ret);}



int	main(/*int argc, char **argv*/)
{
	t_window	*window;
	t_graphon	*graphon;

	window = init_window();
	graphon = (t_graphon*)ft_memalloc(sizeof(t_graphon));
	start_cl(graphon, window);






//	draw_thing(window);
	mlx_hook(window->win_ptr, 17, 1L << 17, close_window, window);
	mlx_hook(window->win_ptr, 2, 1L << 0, key_press, window);
//	mlx_hook(window->win_ptr, 4, 1L << 2, mouse_buttons, window);
	mlx_loop(window->mlx_ptr);



}
