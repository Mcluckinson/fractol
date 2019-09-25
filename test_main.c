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

void			test_mandel(t_window *window)
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
}

void	put_point(int x, int y, t_window *window, int iteration)
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
}

void	draw_thing(t_window *window)
{
mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);
}

# define CHECK_ERROR { if (ret != CL_SUCCESS) exit(ret);}

char *read_file(char *path) {
	char * buffer = 0;
	long length;
	FILE * f = fopen (path, "rb");

	printf("Hi\n");
	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		printf("Hi 2\n");
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose (f);
	}
	return (buffer);
}

int	main(/*int argc, char **argv*/)
{
	t_window *window;

	window = init_window();

//	test_mandel(window);
	int ret;
	cl_platform_id platform_id;
	cl_uint num_platforms;
	ret = clGetPlatformIDs(1, &platform_id, &num_platforms);//////Хуевина типа MLX pointer забей хуй
	CHECK_ERROR /////макрос наверху замени по нормам
	cl_device_id device_id; ////это будет айди видюхи
	cl_uint num_devices;
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &num_devices);////цепляем айди видюхи в девайс айди
	CHECK_ERROR

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);////какой-то ебучий контекст в котором будет лежать кернел и всякая хуйня
	CHECK_ERROR

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);////очередь команд, см млх хуеинтер
	CHECK_ERROR

	char *program_string; /////строка с кодом кернела
	program_string = read_file("/Users/cyuriko/fractol_to_git/test.cl");/////собсна читаем код кернела кладем в эту строку
	size_t len = strlen(program_string);
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&program_string, &len, &ret);/////эта хуйня инициализирует эту программу, поговаривают, что собирает бинарник но хуй пойми. хочет стрлен (см выше)
	CHECK_ERROR

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);/////вот эта хуйня компилирует то что выше вот там блядь посмотри
	if (ret != CL_SUCCESS)//////эта хуйня выведет ошибку если в кернеле написано говно, попробуй написать хуйню в тест.сл
	{
		size_t log_size;
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *log = calloc(log_size + 1, sizeof(char));
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		printf("%s\n", log);
	}
	CHECK_ERROR

	cl_kernel kernel = clCreateKernel(program, "test", &ret);/////инициализация кернела с написанным кодом (читни про эту хуйню еще)
	CHECK_ERROR

	char color[3] = {0xf0, 0x30, 0xa0};
	cl_mem image_mem;/////сл мем это поинтер на слвскую память
	cl_mem color_mem;
	color_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(char) * 3, NULL, &ret);///слевский маллок
	CHECK_ERROR
	image_mem = clCreateBuffer(context, CL_MEM_WRITE_ONLY, MAP_W * MAP_H * sizeof(int), NULL, &ret);
	CHECK_ERROR
	ret = clEnqueueWriteBuffer(command_queue, color_mem, CL_TRUE, 0, sizeof(char) * 3, color, 0, NULL, NULL);////запись с процессора на видопамять
	CHECK_ERROR
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &color_mem);/////установка аргументов которые потом подашь в кернел
	CHECK_ERROR
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), &image_mem);
	CHECK_ERROR
	int a = 20;
	ret = clSetKernelArg(kernel, 2, sizeof(int), &a);

	size_t work_size = MAP_H * MAP_W;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &work_size, NULL, 0, NULL, NULL);//////запуск кернела, ворк сайз кернелов запустит хоть миллион блядь
	CHECK_ERROR

	int *my_image = malloc(sizeof(int) * MAP_H * MAP_W);
	ret = clEnqueueReadBuffer(command_queue, image_mem, CL_TRUE, 0, sizeof(int) * MAP_H * MAP_W, my_image, 0, NULL, NULL);///////чтение с картинки которая теперь в видеопамяти
	CHECK_ERROR

	printf("Start drawing!\n");
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, x, y, my_image[x + y * MAP_W]);
		}
	}




//	draw_thing(window);
//	mlx_hook(window->win_ptr, 17, 1L << 17, close_window, window);
//	mlx_hook(window->win_ptr, 2, 1L << 0, key_press, window);
//	mlx_hook(window->win_ptr, 4, 1L << 2, mouse_buttons, window);
	mlx_loop(window->mlx_ptr);



}
