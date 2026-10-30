// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta; short pad; void (*fn)(void *); };
typedef struct { float a, b, c, d; } F4;
struct G { int x0; int x4; int x8; };
extern struct G D_0036DBE0;
struct S {
    char pad[0xC]; struct VEntry *table;
    char pad1[0xD0 - 0x10]; int iD0;
    char pad2[0x108 - 0xD4]; int i108; int i10C; float f110, f114, f118, f11C;
    char pad3[0x124 - 0x120]; F4 f124;
    char pad4[0x144 - 0x134]; float f144, f148;
    char pad5[0x300 - 0x14C]; char list[0x35C - 0x300]; float f35C; int i360;
    char pad6[0x440 - 0x364]; int i440; float f444;
};
void func_0028FD70(struct S *p);
void func_0011AF38(void *p, int n);
void func_00167AB0(struct S *p, int a, int b, int c, int d);
void func_001667F8(struct S *p);
void func_00166548(struct S *p);
/* inline helper with float parameters: its parameter pseudos give the original store order (0x444 before 0x35C) */
static inline void SetLimits(struct S *p, float a, float b) { p->f444 = b; p->f35C = a; }

void func_00165938(struct S *p)
{
    F4 *pf;
    func_0028FD70(p);
    func_0011AF38(p->list, 0xC);
    p->f114 = 1.0f;
    p->f110 = 1.0f;
    p->f11C = 1.0f;
    p->f118 = 1.0f;
    p->f144 = 100.0f;
    p->f148 = 100000.0f;
    func_00167AB0(p, 0, 0, D_0036DBE0.x4, D_0036DBE0.x8);
    pf = &p->f124;
    pf->a = 0.5f;
    pf->c = 0.1f;
    pf->b = 0.0f;
    pf->d = 10.0f;
    p->table[55].fn((char *)p + p->table[55].delta);
    func_001667F8(p);
    func_00166548(p);
    p->i10C = 0xFF;
    SetLimits(p, -10.0f, -60.0f);
    p->i360 = -1;
    p->iD0 = 0;
    p->i440 = -1;
    p->i108 = 0;
}
