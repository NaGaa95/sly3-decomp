// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Limits { unsigned char prefix[0x70]; float f70; float f74; float f78; float f7C; float f80; };
extern float D_003274C8;
extern float D_003274CC;
void func_001C7340(void *object);
void func_00258F38(struct Limits *limits)
{
    float a,b;
    func_001C7340(limits);
    a=D_003274C8;
    b=D_003274CC;
    limits->f78=b;
    limits->f74=D_003274C8;
    limits->f70=b;
    limits->f7C=500.0f;
    limits->f80=800.0f;
}
