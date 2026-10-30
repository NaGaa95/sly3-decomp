// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct LIST { int x0; void *head; };
struct VEntry { short delta; short pad; void *fn; };
struct O { char pad[0xC]; struct VEntry *table; char pad2[0x28 - 0x10];
           unsigned long b0 : 48; long n : 4; unsigned long b52 : 4; unsigned long grf1 : 8;
           char pad3[0x3C - 0x30]; unsigned int x3C; };
struct S { char pad[0xC]; struct VEntry *table; char pad1[0xD0 - 0x10]; int iD0; char padd[0xE0 - 0xD4]; int xE0, xE4, xE8;
           char pad2[0x300 - 0xEC]; struct LIST list; char pad2b[0x310 - 0x308]; int c; struct O *ao[9]; int x338; int af[4]; int an[4]; char pad3[0x370 - 0x35C]; char ab[0xA0]; char pad4[0x414 - 0x410]; int x414; };
extern char D_0036E740[];
extern char D_00475480[];
int func_00165DC8(struct S *p);
void *memset(void *p, int c, unsigned int n);
void func_001A9240(void *pv, struct S *p);
void func_00165D40(void *g, struct S *p);
void func_00169D98(void *p);
void func_00165C70(void *g, struct S *p);
int func_00168DD8(struct S *p);
void func_001C9118(void *p, int k);
void func_001685C8(struct S *p);
void func_0015B0E8(void *g);
#define VCALL0(o, i) ((void (*)(void *))(o)->table[i].fn)((char *)(o) + (o)->table[i].delta)
#define VCALL1(o, i, a) ((void (*)(void *, int))(o)->table[i].fn)((char *)(o) + (o)->table[i].delta, (a))
void func_00165FC0(struct S *p)
{
    int i;
    if (func_00165DC8(p))
        return;
    if (p->iD0 != -1)
        func_001A9240(D_0036E740 + p->iD0 * 0x11C0, p);
    p->xE8 = 0;
    p->xE4 = 0;
    p->xE0 = 0;
    p->x414 = 0;
    {
        struct LIST *pl = &p->list;
        void *q;
        while ((q = pl->head) != 0)
            func_00169D98(q);
    }
    if (func_00168DD8(p)) {
        for (i = 0; i < p->c; i++) {
            struct O *o = p->ao[i];
            if (p->af[i] & 1)
                VCALL0(o, 9);
            if (p->af[i] & 2)
                VCALL1(o, 23, 1);
            func_001C9118(o, p->an[i]);
        }
        func_001C9118(p, 2);
        VCALL1(p, 23, 0);
    }
    func_00165D40(D_00475480, p);
    VCALL0(p, 9);

}
