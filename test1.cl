__kernel void test(__global unsigned int* img_data)
{
    int gid;

    gid = get_global_id(0);
    unsigned int color = 0x00FF00FF;

    img_data[gid] = color;

}