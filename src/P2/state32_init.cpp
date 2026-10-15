// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct POOLSTATE
{
    int cb;
    int c;
    int cbAlign;
    void *pv;
    int cAlloc;
    void *pvBlock;
    void *PvAlloc();
    void Reset();
    void Free(void *p);
    void WarmUp();
    POOLSTATE(int cb, int c, int cbAlign);
};

extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" POOLSTATE D_004D2AD8, D_004D2BB0, D_004D2C88;
extern "C" POOLSTATE D_004D2D60, D_004D2E38, D_004D2F10;
inline void *operator new(unsigned int cb, void *pv) { return pv; }
typedef unsigned int UQ __attribute__((mode(TI)));
extern "C" const UQ D_00317550;
extern "C" void *memset(void *,int,unsigned int);
// Original 32-byte aligned state: a vector followed by an integer and three zero fields.
struct STATE32 { UQ value; int n; int unknown[3]; };
static inline STATE32 MakeState() { STATE32 state; memset(&state,0,sizeof(state)); state.value=D_00317550; state.n=1; return state; }
extern "C" { STATE32 D_00474FD0 = MakeState(); }
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

