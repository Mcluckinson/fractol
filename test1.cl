__kernel void test(__global unsigned char* img_data)
{
    int gid;

    gid = get_global_id(0);
    int i;
    i = gid * 4;
    unsigned int color = 0x0011A953;

    //img_data[i] = color;
    img_data[i] = 0;
       img_data[i + 1] = color;
       img_data[i + 2] = color >> 8;
       img_data[i + 3] = color >> 16;


}