// Sly 2 reference: src/hand/SendDmaSyncGsFinish__FP10sceDmaChanP2QW.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRITSECT;
struct sceDmaChan;
union QW;
extern CRITSECT D_0036E670;
extern int D_0036E698;
extern int D_0036E694;
void EnterCritSect(CRITSECT *pcs) __asm__("func_00271BB8");
void LeaveCritSect(CRITSECT *pcs) __asm__("func_00271C10");
extern "C" int func_0029F940() __asm__("func_0029F940");
extern "C" void func_0029F900(int n) __asm__("func_0029F900");
extern "C" void func_00293920(int n) __asm__("func_00293920");
extern "C" void func_0029FD20(sceDmaChan *pch, QW *pqw) __asm__("func_0029FD20");
extern "C" void func_002936E0(int sid) __asm__("func_002936E0");
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw) __asm__("func_00195760");
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw)
{
    EnterCritSect(&D_0036E670);
    D_0036E698 = 1;
    *(volatile long *)0x12001000 |= 2;
    func_0029F900(func_0029F940() & ~0x200);
    func_00293920(0);
    func_0029FD20(pch, pqw);
    func_002936E0(D_0036E694);
    LeaveCritSect(&D_0036E670);
}
