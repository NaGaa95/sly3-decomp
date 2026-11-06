// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(void *, qword); };
struct Y { int a[3]; struct VTE *vt; char pad[0xE0 - 0x10]; int xE0; };
struct S { char pad[0x150]; struct Y *x150; char pad2[0x16C - 0x154]; int x16C; };
void *func_002459F8(int id);
void func_00244F08(void *x, int k);
void func_00245000(void *x, qword v);
void func_00245100(void *x, float a, float b);
void func_00244E08(void *x, float g);
void func_001FE728(struct Y *y, int k);
void func_00280BF8(struct S *p, qword v, float g)
{
    if (p->x16C != -1) {
        void *x = func_002459F8(p->x16C);
        func_00244F08(x, 0);
        if (x) {
            func_00245000(x, v);
            func_00245100(x, 100.0f, 1000.0f);
            func_00244E08(x, g);
        }
    }
    if (p->x150) {
        p->x150->xE0 = 0;
        p->x150->vt[34].pf((char *)p->x150 + p->x150->vt[34].d, v);
        func_001FE728(p->x150, 1);
    }
}
