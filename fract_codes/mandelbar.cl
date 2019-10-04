__kernel void test(const double min_re, const double max_re, const double min_im, const double max_im, const double factor_re, const double factor_im, const int map_w, __global unsigned int* img_data, const int max_iteration)
{
    int gid;
    int x;
    int y;
    double	c_re;
    double	c_im;
    double  z_re;
    double  z_im;
    int     iteration = 0;
 //   int     max_iteration = 50;
    double  t;
    unsigned int	color = 0x00ff00ff;

    gid = get_global_id(0);
    y = gid / map_w;
    x = gid % map_w;

    c_im = max_im - y * factor_im;
    c_re = min_re + x * factor_re;
    z_re = c_re;
    z_im = c_im;
    while (pow(z_re, 2.0) + pow(z_im, 2.0) <= 4 && iteration < max_iteration)
    	{
    	    double tmp = z_re;
    		z_re = (pow(z_re, 2.0) - pow(z_im, 2.0)) + c_re;
    		z_im = -2.0 * (tmp * z_im) + c_im;
    		iteration++;
    	}// Формула множества Мандельброта
    t = (double)iteration / (double)max_iteration;
  //  if (t != 0)
    //    printf ("%i\n", t);
   unsigned int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
   unsigned int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
   unsigned int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
  color =red << 16 | green << 8 | blue;

        img_data[gid] = color;
  //  img_data[gid + 1] = green;
   // img_data[gid + 2] = red;

}