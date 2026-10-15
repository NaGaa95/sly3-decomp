// Recovered mission, elapsed time, history and controller text callbacks.
// Provisional structures describe only the fields accessed by these functions.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "game_text.h"
struct CALLBACK_REF { int tag; union { int n;float g;void *pv; } value; CALLBACK_REF(const CALLBACK_REF &); ~CALLBACK_REF(); };
class CFrame { int m_a[4]; public: CFrame(); ~CFrame(); };
extern "C" CALLBACK_REF func_002BC010(int,void *);
extern "C" void func_0012BC20(CALLBACK_REF *);
inline CALLBACK_REF::~CALLBACK_REF() { func_0012BC20(this); }
struct CALLBACK_GAME { char prefix[0x406C]; int option; };
extern "C" CALLBACK_GAME D_00475480;
struct CALLBACK_RECORD { char storage[0x6864]; };
extern "C" CALLBACK_RECORD D_003752B4[];
extern "C" char D_00323DB0[],D_00323DB8[],D_0046F550[];
extern "C" void *func_0025E198(CALLBACK_RECORD *);
extern "C" int func_00222410(void *);
extern "C" int func_0025E6D0(CALLBACK_RECORD *);
extern "C" void func_00271448(char *,const char *,...);
extern "C" int func_001D45B0(void *);
extern "C" void func_001D1EF8(unsigned short *out,int index) {
    CALLBACK_RECORD *record=&D_003752B4[index];
    float value;
    { CALLBACK_REF ref=func_002BC010(D_00475480.option,record); value=ref.value.g; }
    if(value!=0.0f) {
        CFrame frame;
        func_00271730(out,func_00150630(&D_00475480,func_00222410(func_0025E198(record))));
        func_00271828(out,D_00323DB0);
        char text[32];
        func_00271448(text,D_00323DB8,func_0025E6D0(record));
        func_00271828(out,text);
    } else {
        switch(func_001D45B0(D_0046F550)) {
        case 42:case 43:func_00271730(out,func_00150630(&D_00475480,84));break;
        case 37:func_00271730(out,func_00150630(&D_00475480,85));break;
        }
    }
}

extern "C" float D_0036BB98,D_0047A3E0;
extern "C" const char D_00327EE0[];
extern "C" void func_00271448(char *, const char *, ...);
extern "C" void func_0025F158(unsigned short *out) {
    char text[32];
    float start=D_0036BB98;
    float elapsed=D_0047A3E0-start;
    int time=(int)(elapsed > 0.0f ? elapsed : 0.0f);
    int minutes=time/60;
    func_00271448(text,D_00327EE0,minutes,time-minutes*60);
    func_002717E0(out,text);
}
struct HISTORY_ITEM { int stringId; char padding[28]; };
struct HISTORY { int count; HISTORY_ITEM *items; int unknown[3]; int current; int unknown18; };
extern "C" HISTORY D_0046F570[];
extern "C" int D_0046F588;
extern "C" void func_0025F440(unsigned short *out,int delta) {
    HISTORY *history=&D_0046F570[D_0046F588];
    if (history->count) {
        int offset=history->current; offset-=3; int n=delta+offset;
        while(n<0) n+=history->count;
        func_00271730(out,func_00150630(&D_00475480,history->items[n%history->count].stringId));
    }
}
extern "C" unsigned char D_004BC220[];
extern "C" void func_0027ED60(void *,void *);
extern "C" void func_0027EEC8(void *,unsigned short *);
extern "C" void func_0025F598(unsigned short *out) { func_0027ED60(D_004BC220,out); }
extern "C" void func_0025F5C0(unsigned short *out) { func_0027EEC8(D_004BC220,out); }
extern "C" void func_0017C9B0(void *) {}
