// Sly 2 reference: src/hand/SetScrollerMasterSpeeds__FP8SCROLLERff.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SCROLLER { char pad[0x60]; float su; float sv; };
void SetScrollerMasterSpeeds(SCROLLER *pscroller, float su, float sv) __asm__("func_00237DD8");
void SetScrollerMasterSpeeds(SCROLLER *pscroller, float su, float sv)
{
    pscroller->su = su;
    pscroller->sv = sv;
}
