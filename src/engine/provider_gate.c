// SLY3_CFLAGS: -Os -G0
struct EngineGateItem { unsigned char prefix[0x54]; int value; };
struct EngineGateProvider { unsigned char prefix[0x14]; struct EngineGateItem *item; };
extern struct EngineGateProvider D_004BC230;
int func_002852B0(void *provider);
int func_0018ADB0(void);
int func_0018AE00(void)
{
    if(func_002852B0(&D_004BC230) && D_004BC230.item->value) return 1;
    return func_0018ADB0();
}
