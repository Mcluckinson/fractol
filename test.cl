

__kernel void test(__global unsigned char* color, __global int* image, const int mod)
{
	int gid = get_global_id(0);
	unsigned char clr = (sin((float)gid / 10000.0) + 1) / 2.0 * 255;
	image[gid] = (clr - mod) << 16 | (color[1] - mod) << 8 | (color[2] - mod);
}