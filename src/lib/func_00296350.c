// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64
typedef struct RuntimeSifFileSlot {
    unsigned int opaque[4];
} RuntimeSifFileSlot;

extern RuntimeSifFileSlot D_004CC500[32];
extern int D_0034A6A8;
void func_00296160(void);
int func_002936E0(int semaphore);
int func_002936C0(int semaphore);

RuntimeSifFileSlot *func_00296350(int descriptor)
{
    RuntimeSifFileSlot *slot;
    func_00296160();
    func_002936E0(D_0034A6A8);
    if ((unsigned int)descriptor < 32) {
        slot = &D_004CC500[descriptor];
        func_002936C0(D_0034A6A8);
        return slot;
    }
    func_002936C0(D_0034A6A8);
    return 0;
}

typedef char RuntimeSifFileSlotSize16[(sizeof(RuntimeSifFileSlot) == 16) ? 1 : -1];
typedef char RuntimeSifFileSlotAlignment4[(__alignof__(RuntimeSifFileSlot) == 4) ? 1 : -1];
