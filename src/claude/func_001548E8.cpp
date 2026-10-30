// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "../../include/eval_dispatch_api.h"
}
class REF {
public:
    CRef value;
    REF() {}
    REF(int n) { value.tag = 0x13; value.payload.integer = n; }
    REF(const REF &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~REF() { Drop(); }
};
struct SLOT { int id; int x4; float t; };
struct P;
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x3A8]; VTE e3A8; char pad2[0x3B8 - 0x3B0]; VTE e3B8; };
struct P { char pad[0xC]; VT *pvt; char pad1[0x1108 - 0x10]; void *p1108; char pad2[0x1250 - 0x110C]; SLOT aslot[3]; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern int D_0036DBE0;
extern const char D_00320590[];
extern const char D_00320598[];
void func_00154350(P *p, SLOT *ps, int n);
int func_00154330(int id);
int func_00271448(char *buf, const char *fmt, ...);
REF func_0021CF20(const REF &value, const char *path, ...);
int func_00173560(int id);
void func_00172C30(void *p, int k);
void func_001548E8(P *p, unsigned int i, int id);
}

void func_001548E8(P *p, unsigned int i, int id)
{
    SLOT *ps;
    int f, j;
    if (i >= 3)
        return;
    ps = &p->aslot[i];
    if (ps->id == id)
        return;
    func_00154350(p, ps, -1);
    ps->id = id;
    ps->x4 = 0;
    ps->t = g_clock.t;
    f = func_00154330(id);
    for (j = 0; j < 3; j++) {
        SLOT *pj = &p->aslot[j];
        int g = func_00154330(pj->id);
        if (j != i && (pj->id == id || (f && g))) {
            func_00154350(p, pj, -1);
            pj->id = -1;
        }
        int fWrite = D_0036DBE0 != 2;
        if (fWrite) {
            char buf[16];
            func_00271448(buf, D_00320590, j);
            func_0021CF20(REF(p->aslot[j].id), ((const char *(*)(void *))p->pvt->e3A8.pfn)((char *)p + p->pvt->e3A8.d), D_00320598, buf, 0);
        }
    }
    ((void (*)(void *))p->pvt->e3B8.pfn)((char *)p + p->pvt->e3B8.d);
    {
        int k = func_00173560(ps->id);
        if (k != -1)
            func_00172C30(p->p1108, k);
    }
}
