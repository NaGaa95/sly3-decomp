// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00176750): switch the AI state and spawn the matching behaviour object.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct B2 { qword q[2]; };
struct X14 { char pad[0x14]; int n14; };
struct F { int a; int n4; float f8; int pad; } __attribute__((aligned(16)));
struct O {
    char pad[0xC]; struct VTE *vt; char pad2[0x20];
    union { struct { int n30; int pad34; int n38; int n3C; union { qword v40; float f40; } u40; } s; struct B2 b; } u30;
    char pad50[0xC]; int n5C;
};
struct A { char pad[0x29C]; char a29C[0x10D8 - 0x29C]; int n10D8; int pad10DC; qword v10E0; char pad10F0[0x1164 - 0x10F0]; int n1164; char pad1168[0x1190 - 0x1168]; int n1190; char pad1194[0x11C8 - 0x1194]; void *p11C8; };
struct S { char pad[0x10]; struct A *p10; int pad2; char a18[0x18]; struct F f30; float f40; float f44; };
/* .rodata of the original unit at 0x00321D70 (it precedes the jump table). */
static const float D_00321D70[2] = { 3.0f, 5.0f };
int func_0019B208(struct F *a, struct F *b);
void func_00240DB0(struct A *p);
void func_00238AE8(void *p);
int func_00257EF8(struct A *p);
struct O *func_00238690(void *p, int n);
void func_00197838(struct O *o, int a, int b, int c);
void func_001A6B00(struct O *o, int n);
void func_002BC760(void *p, int n);
int func_001A29B0(void *p);
float func_0011E940(float a, float b);
#define VCALL(o) { struct VTE *e = &(o)->vt[8]; e->pfn((char *)(o) + e->d); }
void func_0019A2D0(struct S *p, struct F *m)
{
    if (func_0019B208(m, &p->f30))
        return;
    if (p->f30.a == 0x11)
        func_00240DB0(p->p10);
    func_00238AE8(p->a18);
    if (func_00257EF8(p->p10) && (m->a == 1 || m->a == 4)) {
        m->a = 0x16;
        m->n4 = 1;
    }
    p->f30 = *m;
    p->f40 = g_clock.t;
    switch (m->a) {
    case -1:
    case 0:
        break;
    case 5:
        { struct O *o = func_00238690(p->p10->a29C, 0xD3); func_00197838(o, m->n4, 1, 0); VCALL(o) }
        break;
    case 1:
        { struct O *o = func_00238690(p->p10->a29C, 0xD4); VCALL(o) }
        break;
    case 3:
        { struct O *o = func_00238690(p->p10->a29C, 0xC9); o->u30.s.n3C = 0x11; o->u30.s.n38 = m->n4; VCALL(o) }
        break;
    case 4:
        { struct O *o = func_00238690(p->p10->a29C, 0xD2); o->u30.s.n30 = m->n4; VCALL(o) }
        break;
    case 2:
        { struct O *o = func_00238690(p->p10->a29C, 0xD5); func_001A6B00(o, m->n4); VCALL(o) }
        break;
    case 9:
        { struct O *o = func_00238690(p->p10->a29C, 0xCE); func_002BC760(&o->u30, m->n4); VCALL(o) }
        break;
    case 10:
        { struct O *o = func_00238690(p->p10->a29C, 0xCF); func_002BC760(&o->u30, m->n4); VCALL(o) }
        break;
    case 11:
        { struct O *o = func_00238690(p->p10->a29C, 0xD0); func_002BC760(&o->u30, m->n4); VCALL(o) }
        break;
    case 8:
        { struct O *o = func_00238690(p->p10->a29C, 0xD8); VCALL(o) }
        break;
    case 6:
        { struct O *o = func_00238690(p->p10->a29C, 0xD9); o->u30.s.n3C = p->f30.n4; VCALL(o) }
        break;
    case 7:
        { struct O *o = func_00238690(p->p10->a29C, 0xDA); o->n5C = ((struct X14 *)m->n4)->n14; VCALL(o) }
        break;
    case 12:
        { struct O *o = func_00238690(p->p10->a29C, 0xDB); VCALL(o) }
        break;
    case 13:
        { struct O *o = func_00238690(p->p10->a29C, 0xDD); o->u30.s.n38 = m->n4; VCALL(o) }
        break;
    case 18:
        { struct O *o = func_00238690(p->p10->a29C, 0xD7); o->u30.s.n38 = p->p10->n1164; o->u30.s.n3C = p->p10->n1190; VCALL(o) }
        break;
    case 14:
        { struct O *o = func_00238690(p->p10->a29C, 0xDE); o->u30.s.n30 = p->p10->n10D8; o->u30.s.u40.v40 = p->p10->v10E0; VCALL(o) }
        break;
    case 15:
        { struct O *o = func_00238690(p->p10->a29C, 0xCA); o->u30.s.n3C = 0x2E; o->u30.s.n38 = m->n4; VCALL(o) }
        { float t = g_clock.t; p->f44 = t + func_0011E940(D_00321D70[0], D_00321D70[1]); }
        break;
    case 16:
        { struct O *o = func_00238690(p->p10->a29C, 0xE3); o->u30.s.n38 = m->n4; o->u30.s.u40.f40 = m->f8; VCALL(o) }
        break;
    case 17:
        { struct O *o = func_00238690(p->p10->a29C, 0xE5); o->u30.b = *(struct B2 *)m->n4; VCALL(o) }
        break;
    case 19:
        { struct O *o = func_00238690(p->p10->a29C, 0xE8); o->u30.s.n38 = func_001A29B0(p->p10->p11C8); VCALL(o) }
        break;
    case 20:
        { struct O *o = func_00238690(p->p10->a29C, 0xE9); VCALL(o) }
        break;
    case 21:
        { struct O *o = func_00238690(p->p10->a29C, 0xEA); o->u30.s.n38 = m->n4; VCALL(o) }
        break;
    case 22:
        { struct O *o = func_00238690(p->p10->a29C, 0xEB); o->u30.s.n3C = m->n4; VCALL(o) }
        break;
    case 23:
        { struct O *o = func_00238690(p->p10->a29C, 0xE7); o->u30.s.n30 = m->n4; VCALL(o) }
        break;
    }
}
