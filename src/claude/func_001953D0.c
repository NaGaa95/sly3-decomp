// SLY3_CFLAGS: -Os -G0
// Vertical-blank handler: pick the display environment for the current field, write it to the GS
// privileged registers, and blend the two circuits by one line when the frame buffer does not
// match the field.  Sly 2 counterpart: BlendDisplayOnBufferMismatch.
//
// The register images are 4-byte aligned structures, so every copy is a block move with
// alignment 4: GCC emits ldl/ldr + sdl/sdr, and because 8 bytes is not more than twice the
// alignment it writes the absolute GS address directly instead of loading it into a scratch.
typedef struct {
    unsigned long word;
} __attribute__((packed, aligned(4))) GsReg;

typedef union {
    GsReg reg;
    struct {
        unsigned long EN1 : 1, rest : 63;
    } __attribute__((packed)) bits;
} __attribute__((packed, aligned(4))) GsPmode;

typedef union {
    GsReg reg;
    struct {
        unsigned int FBP : 9, FBW : 6, PSM : 5, reserved0 : 12, DBX : 11, DBY : 11, reserved1 : 10;
    } __attribute__((packed)) bits;
} __attribute__((packed, aligned(4))) GsDispfb;

typedef union {
    GsReg reg;
    struct {
        unsigned int DX : 12, DY : 11, MAGH : 4, MAGV : 2, reserved0 : 3, DW : 12, DH : 11, reserved1 : 9;
    } __attribute__((packed)) bits;
} __attribute__((packed, aligned(4))) GsDisplay;

typedef struct {
    GsPmode pmode;
    GsReg smode2;
    GsDispfb dispfb;
    GsDisplay display;
    GsReg bgcolor;
} DisplayEnvironment;

typedef struct {
    int options;
    char pad[0x48];
    DisplayEnvironment env[2];
} DisplayState;

extern DisplayState D_0036DBEC;
extern int D_0036DC94, D_0036DCA0[2], D_0036DCA8, D_0036E690, D_0036E69C;
int func_002936D0(int semaphore);

#define GS_PMODE (*(GsPmode *)0x12000000)
#define GS_SMODE2 (*(GsReg *)0x12000020)
#define GS_DISPFB2 (*(GsDispfb *)0x12000090)
#define GS_DISPLAY2 (*(GsDisplay *)0x120000A0)
#define GS_BGCOLOR (*(GsReg *)0x120000E0)
#define GS_DISPFB1 (*(GsDispfb *)0x12000070)
#define GS_DISPLAY1 (*(GsDisplay *)0x12000080)

int func_001953D0(void)
{
    int field;
    int selected;
    int options;
    const DisplayEnvironment *env;

    D_0036DCA8++;
    field = (*(const unsigned int *)0x12001000 >> 13) & 1;
    if (D_0036DCA0[0] == field || D_0036DCA0[1] == field) {
        if (D_0036DCA0[0] != field)
            D_0036DC94 = 1;
        else if (D_0036DCA0[1] != field)
            D_0036DC94 = 0;
    } else if (D_0036DCA0[0] == -1) {
        if (D_0036DCA0[1] != D_0036DCA0[0])
            D_0036DC94 = 1;
    } else {
        D_0036DC94 = 0;
    }
    selected = D_0036DC94;
    env = &D_0036DBEC.env[selected];
    options = D_0036DBEC.options & 3;
    GS_PMODE = env->pmode;
    GS_SMODE2 = env->smode2;
    GS_DISPFB2 = env->dispfb;
    GS_DISPLAY2 = env->display;
    GS_BGCOLOR = env->bgcolor;
    if (!options && D_0036DCA0[selected] != field) {
        GsPmode pmode = env->pmode;
        GsDisplay display = env->display;
        GsDispfb dispfb = env->dispfb;
        display.bits.DH--;
        if (field)
            dispfb.bits.DBY++;
        else
            display.bits.DY++;
        pmode.bits.EN1 = 1;
        GS_DISPLAY1 = display;
        GS_DISPFB1 = dispfb;
        GS_PMODE = pmode;
    }
    if (D_0036E69C) {
        D_0036E69C = 0;
        func_002936D0(D_0036E690);
    }
    __asm__ __volatile__("sync\n\tei" : : : "memory");
    return 0;
}
