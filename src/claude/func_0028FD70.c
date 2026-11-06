// SLY3_CFLAGS: -Os -G0
// Adapted from Sly 2 InitXfm__FP3XFM (func_00231100).
typedef struct S { char pad[0x10]; struct S *x10; char pad2[0x2C]; int x40; int x44; char pad3[0x8]; float m[16]; } S;
void func_001C7340(S *);
void *func_00292034(void *, int, int);
void func_0028FD70(S *p)
{
    float *m;
    func_001C7340(p);
    if (p->x10)
        p->x40 = *(int *)((char *)p->x10 + 0x50);
    m = p->m;
    func_00292034(m, 0, 0x40);
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    p->x44 = -1;
}
