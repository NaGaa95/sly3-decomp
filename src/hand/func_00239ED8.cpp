// Sly 2 reference: src/hand/func_001F0850.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x30 - 0x10]; void *p30; char pad3[0x44 - 0x34]; float g; };
extern "C" int func_00239CC0(P *) __asm__("func_00239CC0");
extern "C" void func_00138B68(void *, float) __asm__("func_00138B68");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
extern "C" void func_00239ED8(P *p, float g) __asm__("func_00239ED8");
extern "C" void func_00239ED8(P *p, float g)
{
    if (!func_00239CC0(p)) {
        Lock l(p);
        p->g = g;
        if (p->p30) func_00138B68(p->p30, g);
    }
}
