// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Self { unsigned char pad[0x11C]; float g; };
int func_001A1190(struct Self *p, float *pg)
{
    pg[0] = p->g * -3.1415927f;
    pg[1] = p->g * 3.1415927f;
    return 1;
}
