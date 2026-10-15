// Sly 2 reference: src/hand/ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ASEG; struct ALO;
struct VTE { short d; short pad; void (*pfn)(); };
struct ASEGA { int pad[3]; VTE *vt; };
void func_00137628(ASEGA **) __asm__("func_00137628");
void ApplyAseg(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega) __asm__("func_00136908");
void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega) __asm__("func_00137588");
void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega)
{
    func_00137628(ppasega);
    if (paseg)
    {
        ApplyAseg(paseg, paloRoot, t, svt, grfapl, ppasega);
        ASEGA *pasega = *ppasega;
        ((void (*)(void *))pasega->vt[1].pfn)((char *)pasega + pasega->vt[1].d);
    }
}
