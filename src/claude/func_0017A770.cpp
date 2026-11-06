// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Static initialization (g++ __static_initialization_and_destruction_0) of the emitter defaults and six slot heaps.
// Port of Sly 2 func_0015CAD8 (references/sly2/src/hand/func_0015CAD8.cpp); pool refs as in src/P2/heap_init.cpp.
// Needs config/object_symbol_addrs.json: __static_initialization_and_destruction_0 -> 0x0017A770
// (optionally _GLOBAL_$I$* -> 0x0017A9B8, currently matched by src/auto/func_0017A9B8.c).
//
// D_0036BD50 / D_0036BD90 are the EMITO / EMITV defaults that func_00159118 (InitEmitb) copies into EMITB+0x10 /
// +0x50 (Sly 1's InitEmitb builds the same two objects as guarded local statics). Their initializers hold the
// non-constant vectors D_00317560 (0,0,0), D_00317530 (1,0,0) and D_00317550 (0,0,1), so g++ builds each one in a
// func_00292034 stack temp and block-copies it.
//
// The three unions are what matched it: store_constructor emits a (clobber (mem:BLK)) for every union initializer.
// - EMITV+0x60 is a CLQ (Sly 1 util.h: union of {g0, g1, g2, gUnused} and ag[4]) = {1, 0, -1}. Its clobber is a
//   scheduler barrier, so its two stores issue last and 1.0 / -1 die only there (the game's store order).
// - the union at EMITO+0x20 sits inside the live ranges of the first sentry %hi's only: those of D_0036AE7C / E8 grow
//   to 150 / 168 insns against 146 / 164 for D_0036AE84 / F0, which breaks their global-alloc ties (s4/s3, s6/s5),
//   and it fixes the D_00317560 / D_00317530 v0/v1 choice.
// - the union at EMITV+0x00 fixes the FPU numbers of 1.0 / -1500, the 200 / loop-end registers and the s1/a2 order.
//
// The pool sentries are the CPoolRef counters D_0036AE78..8C (see src/P2/heap_init.cpp).
typedef int qword __attribute__((mode(TI)));

// Sly 1 util.h CLQ: quadratic g0 + x*(g1 + x*g2).
union CLQ {
    struct { float g0, g1, g2, gUnused; };
    float ag[4];
};

// 16-byte vector views; the field names of these two are unknown.
union QWV { qword qw; float ag[4]; };
union G4V { struct { float g0, g4, g8, gC; }; float ag[4]; };

struct EMITO {
    int x0[4];
    int x10;
    int x14[3];
    QWV v20;
    qword v30;
};

struct EMITV {
    G4V g0;
    int x10, x14;
    float x18;
    int x1C;
    qword v20;
    int x30;
    int x34;
    float x38, x3C;
    int x40[8];
    CLQ clq60;
};

typedef char check_emito[(sizeof(EMITO) == 0x40) ? 1 : -1];
typedef char check_emitv[(sizeof(EMITV) == 0x70) ? 1 : -1];

extern "C" qword D_00317560, D_00317530, D_00317550;

extern "C" EMITO D_0036BD50;
EMITO D_0036BD50 = { {0, 0, 0, 0}, -1, {0, 0, 0}, {D_00317560}, D_00317530 };
extern "C" EMITV D_0036BD90;
EMITV D_0036BD90 = { {{750.0f, 750.0f, -1.0f, 1.0f}}, 0, 0, -1500.0f, 0, D_00317550, 0, 200, 1.0f, 1.0f,
                     {0, 0, 0, 0, 0, 0, 0, 0}, {{1.0f, 0.0f, -1.0f}} };


struct POOLSTATE
{
    int cb, c, cbAlign;
    void *pv;
    int cAlloc;
    void *pvBlock;
    POOLSTATE(int cb, int c, int cbAlign);
};

extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" POOLSTATE D_004D2AD8, D_004D2BB0, D_004D2C88;
extern "C" POOLSTATE D_004D2D60, D_004D2E38, D_004D2F10;

inline void *operator new(unsigned int cb, void *pv) { return pv; }

template<int cb, int c, int *pcRef, POOLSTATE *pstate>
class CPoolRef
{
public:
    CPoolRef()
    {
        if (++*pcRef == 1)
            new (pstate) POOLSTATE(cb, c, 16);
    }
};

CPoolRef<16, 2048, &D_0036AE78, &D_004D2AD8> g_ref16;
CPoolRef<24, 1024, &D_0036AE7C, &D_004D2BB0> g_ref24;
CPoolRef<24, 256, &D_0036AE80, &D_004D2C88> g_ref24Small;
CPoolRef<28, 1024, &D_0036AE84, &D_004D2D60> g_ref28;
CPoolRef<12, 256, &D_0036AE88, &D_004D2E38> g_ref12;
CPoolRef<24, 256, &D_0036AE8C, &D_004D2F10> g_ref24Other;
