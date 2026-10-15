// Sly 2 reference: src/hand/func_00217C20.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct T { char pad[8]; short h8; };
struct S { char pad[8]; T *pt; char padc[0x1C]; int x28; };
struct RGBA { unsigned int u; RGBA(unsigned int x) { u = x; } } __attribute__((aligned(16)));
extern "C" char D_00317FC0[];
extern "C" void func_00267860(S *p, int i) __asm__("func_00267860");
extern "C" void func_00267110(S *p, int i, int z, void *q, float f, const RGBA &c0, const RGBA &c1) __asm__("func_00267110");
extern "C" void func_00266FA0(S *p, int i) __asm__("func_00266FA0");
extern "C" void func_00266FA0(S *p, int i)
{
    if (p->x28) {
        if (p->pt->h8 >= 0)
            func_00267860(p, i);
        RGBA c0(0x7F7F7F7F), c1(0xFFFFFFFF);
        func_00267110(p, i, 0, D_00317FC0, 0.0f, c0, c1);
    }
}
