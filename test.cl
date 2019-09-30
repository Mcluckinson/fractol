__kernel void test(__global int* img_data)
{
    int gid;

    gid = get_global_id(0);
    img_data[gid] = 3592107;

}