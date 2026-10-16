// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct FrameSubmitView;
struct FrameWaitFlagsPrefix {
    char unknown[0x30];
    unsigned int flags;
};
extern "C" {
extern FrameSubmitView *D_0036C680;
extern int D_0036C688, D_0036DC98, D_0036DC90, D_0036DCA0[];
extern unsigned int D_0036DBEC;
extern volatile int D_0036C68C;
extern char D_0036C330[];
int func_002936E0(int semaphore);
int func_002936C0(int semaphore);
void func_00183370(FrameSubmitView *frame,int display,int unused,int sendGIFS);
void func_001837E0(void);
void func_001956B8(void);
void func_001834F8(FrameSubmitView *frame);
void func_001F15C0(int transportedUnusedPhase);
}
extern "C" void func_00183668(int reset)
{
    unsigned int i;
    for (i=0;i<2;++i)
        func_002936E0(D_0036C688);
    for (i=0;i<2;++i)
        func_002936C0(D_0036C688);
    while (!D_0036C68C)
        ;
    if (reset) {
        if (D_0036C680) {
            int display=D_0036DC98;
            for (int count=2;count>=0;--count) {
                func_00183370(D_0036C680,display,0,1);
                if (reinterpret_cast<FrameWaitFlagsPrefix *>(D_0036C680)->flags&1)
                    func_001837E0();
                if (reinterpret_cast<FrameWaitFlagsPrefix *>(D_0036C680)->flags&2)
                    func_001956B8();
                display=!display;
                if (D_0036DBEC&3)
                    display=0;
            }
            D_0036DCA0[D_0036DC90]=display;
        }
        for (i=0;i<2;++i)
            func_001834F8(reinterpret_cast<FrameSubmitView *>(D_0036C330+i*0x190));
    }
    func_001F15C0(3);
    D_0036C680=0;
}
