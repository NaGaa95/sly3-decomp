// Sly 2 reference: src/hand/EnterCritSect__FP8CRITSECT.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRITSECT { int cEnter; int thread; int sema; };
extern "C" int func_00293590(void) __asm__("func_00293590");
extern "C" int func_002936E0(int sema) __asm__("func_002936E0");

void EnterCritSect(CRITSECT *pcritsect) __asm__("func_00271BB8");
void EnterCritSect(CRITSECT *pcritsect)
{
    int threadId = func_00293590();

    if (threadId != pcritsect->thread)
    {
        func_002936E0(pcritsect->sema);
        pcritsect->thread = threadId;
        pcritsect->cEnter = 1;
    }
    else
    {
        pcritsect->cEnter++;
    }
}
