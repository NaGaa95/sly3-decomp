// SLY3_CFLAGS: -Os -G0
struct StartChoice { unsigned char opaque00[8]; int mode; };
struct StartProviderState { unsigned char opaque00[0x54]; int enabled; };
struct StartProvider {
    unsigned char opaque00[0x14];
    struct StartProviderState *state;
};
extern struct StartProvider D_004BC230;
extern void *D_004794CC;
extern int D_0036DBA4;
int func_002852B0(void *provider);
int func_0018ADB0(void);
void func_00189F38(void *subject, unsigned int flags);

void func_001D54A0(struct StartChoice *request)
{
    int mode = request->mode;
    if (!func_002852B0(&D_004BC230) || !D_004BC230.state->enabled) {
        if ((mode == 1 && func_0018ADB0()) ||
            (mode == 0 && !func_0018ADB0()))
            mode = -1;
    }
    D_0036DBA4 = mode;
    func_00189F38(D_004794CC, 0x102);
}
