// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta; short pad; void *fn; };
struct O { char pad[0xC]; struct VEntry *table; char pad2[0x28 - 0x10];
           unsigned long b0 : 48; long n : 4; unsigned long b52 : 4; unsigned long grf1 : 8;
           char pad3[0x3C - 0x30]; unsigned int x3C; };
struct S { char pad[0xC]; struct VEntry *table; char pad1[0xD0 - 0x10]; int iD0;
           char pad2[0x310 - 0xD4]; int c; struct O *ao[9]; int x338; int af[4]; int an[4]; char pad3[0x370 - 0x35C]; char ab[0xA0]; };
extern char D_0036E740[];
extern char D_00475480[];
int func_00165DC8(struct S *p);
void *memset(void *p, int c, unsigned int n);
void func_001A91E0(void *pv, struct S *p);
void func_00165C70(void *g, struct S *p);
int func_00168DD8(struct S *p);
void func_001C9118(void *p, int k);
void func_001685C8(struct S *p);
void func_0015B0E8(void *g);
#define VCALL0(o, i) ((void (*)(void *))(o)->table[i].fn)((char *)(o) + (o)->table[i].delta)
#define VCALL1(o, i, a) ((void (*)(void *, int))(o)->table[i].fn)((char *)(o) + (o)->table[i].delta, (a))
void func_00165DF0(struct S *p)
{
    int i;
    if (!func_00165DC8(p))
        return;
    memset(p->ab, 0, 0xA0);
    if (p->iD0 != -1)
        func_001A91E0(D_0036E740 + p->iD0 * 0x11C0, p);
    func_00165C70(D_00475480, p);
    if (func_00168DD8(p)) {
        for (i = 0; i < p->c; i++) {
            struct O *o = p->ao[i];
            p->af[i] = 0;
            if (!(o->grf1 & 1)) {
                p->af[i] = 1;
                VCALL0(o, 8);
            }
            if (p->x338) {
                unsigned int v = o->x3C;
                if ((v ^ 1) & 1)
                    v = *(unsigned int *)v;
                if (v & 8) {
                    p->af[i] |= 2;
                    VCALL1(o, 23, 0);
                }
            }
            p->an[i] = o->n;
            func_001C9118(o, 1);
        }
        func_001C9118(p, 1);
        VCALL1(p, 23, 1);
        VCALL0(p, 8);
    }
    func_001685C8(p);
    func_0015B0E8(D_00475480);

}
