// SLY3_CFLAGS: -Os -G0
// Port of Sly 2 func_00231300 (src/hand/func_00231300.c).
typedef struct { float x, y, z, w; } V4;
typedef struct { V4 r[3]; } M3 __attribute__((aligned(16)));
typedef struct { char pad[0x40]; int x40; char pad2[0xC]; M3 m; } S;
M3 func_0028EA00(int, int, int); void func_00290078(S *);
static inline void SetM(M3 *pm, M3 m)
{
    *pm = m;
    pm->r[0].w = 0;
    pm->r[1].w = 0;
    pm->r[2].w = 0;
}
void func_0028FF70(S *p, int x)
{
    SetM(&p->m, func_0028EA00(0, p->x40, x));
    func_00290078(p);
}
