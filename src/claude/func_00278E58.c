// SLY3_CFLAGS: -Os -G0
// func_00278E58: state change (exit actions for 1/2, enter actions for 2).
struct VTE { short d; short pad; void (*pf)(void *); };
struct T { char pad0[0xC]; struct VTE *vt; char pad[0x2F - 0x10]; unsigned long flags : 8; };
struct O { char pad[0xC]; struct VTE *vt; char pad1[0xBC - 0x10]; int xBC; };
struct E { int a, b; };
struct S {
    char pad[0x40]; int x40; float g44; void *x48; int pad4C; struct O *x50; int pad54; struct E a58[1];
    char pad1[0x158 - 0x60]; int x158; char pad2[0x25C - 0x15C]; int x25C; int x260; char pad3[0x26C - 0x264];
    struct T *x26C; struct T *x270; void *x274; int x278; int x27C; void *x280; char pad4[0x28C - 0x284]; int x28C; char pad5[0x298 - 0x290]; int x298;
};
extern struct CLOCK { float t; } D_0036BB98;
extern char D_0036C700[];
void func_002412C8(struct T *pt, float f);
void func_001854C8(void *p, int n, struct S *s);
void *func_001F4A80(void *p);
void func_00169C40(void **pp);
void func_00166548(void *p);
void func_002799A0(struct T *pt, void *p);
void *func_00169BF8(int n);
void *func_002799C0(void *a, void *b, int n, struct S *p);
void func_00169CE0(void *p);
int func_002795C0(struct S *p, struct E *pe);
void func_002793A0(struct S *p);
void func_00279450(struct S *p, int k);
int func_00279660(struct S *p);
void func_00278E58(struct S *p, int state)
{
    if (p->x40 == state)
        return;
    switch (p->x40) {
    case 1:
        if (state == 0) {
            if (p->x26C->flags & 1)
                func_002412C8(p->x26C, 0.5f);
            if (p->x270->flags & 1)
                func_002412C8(p->x270, 0.5f);
        }
        break;
    case 2: {
        void *o;
        func_001854C8(D_0036C700, 0x56, p);
        o = func_001F4A80(p->x48);
        func_00169C40(&p->x280);
        if (o)
            func_00166548(o);
        if (p->x50)
            p->x50->vt[54].pf((char *)p->x50 + p->x50->vt[54].d);
        if (p->x274) {
            if (++p->x260 >= 5)
                p->x25C = 1;
        }
        func_002799A0(p->x26C, p->x274);
        p->x274 = 0;
        p->x298 = 0;
        break;
    }
    }
    p->x40 = state;
    p->g44 = D_0036BB98.t;
    if (state == 2) {
        void *o;
        func_001854C8(D_0036C700, 0x55, p);
        o = func_001F4A80(p->x48);
        p->x280 = func_002799C0(func_00169BF8(0x40), o, 0xA, p);
        func_00169CE0(p->x280);
        p->x27C = 0;
        p->x28C = 0;
        p->x26C->vt[8].pf((char *)p->x26C + p->x26C->vt[8].d);
        p->x270->vt[8].pf((char *)p->x270 + p->x270->vt[8].d);
        if (p->x278 == 0) {
            if (func_002795C0(p, p->a58)) {
                func_001854C8(D_0036C700, 0x57, p);
                func_002793A0(p);
            }
        }
        if (p->x278 > 0 && func_002795C0(p, &p->a58[p->x278 - 1])) {
            p->x298 = 1;
            func_00279450(p, 1);
        } else {
            p->x298 = 0;
        }
        if (p->x50) {
            if ((p->x298 && p->x278 < p->x158) || p->x278 == 0)
                p->x50->xBC = func_00279660(p);
            else
                p->x50->xBC = -1;
            p->x50->vt[56].pf((char *)p->x50 + p->x50->vt[56].d);
        }
    }
}
