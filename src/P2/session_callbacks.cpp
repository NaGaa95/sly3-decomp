// Recovered session label, status, count, elapsed time, caption and node callbacks.
// Structure names are provisional; accessed offsets and strides are original.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "game_text.h"
#include "session.h"
extern "C" SESSION_CONTROL_GAME D_00475480;
extern "C" SESSION_CONTROL_DATA *D_0047A3E8;
extern "C" SESSION_CONTROL_NODE *D_004BC244;
extern "C" unsigned char D_00468D30[];
extern "C" int D_00344F00[];
extern "C" float func_0025E1F0(int,void *);
extern "C" int func_0025E5E8(int,void *);
extern "C" void func_00271448(char *,const char *,...);
extern "C" void func_00271530(char *,unsigned int,const char *,...);
extern "C" float fmodf(float,float);
extern "C" const char D_00321718[],D_00321720[],D_00321730[],D_00321738[],D_00321740[],D_00321748[];

extern "C" void func_0017C730(unsigned short *out,int delta) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    int offset=session->index;offset-=3;
    int index=delta+offset;
    if(index>=0&&index<=session->maximum)
        func_00271730(out,func_00150630(&D_00475480,D_00344F00[index]));
}

extern "C" void func_0017C7A8(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session&&func_0025E1F0(session->index,D_00468D30)<=0.0f)
        func_00271730(out,func_00150630(&D_00475480,133));
    else func_00271730(out,func_00150630(&D_00475480,134));
}

extern "C" void func_0017C848(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_0047A3E8;
    if(session) {
        char text[32];
        int n=func_0025E5E8(session->index,D_00468D30);
        func_00271448(text,D_00321718,n);
        func_002717E0(out,text);
    }
}

extern "C" void func_0017C8A8(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_0047A3E8;
    if(session) {
        char text[32];
        float seconds=func_0025E1F0(session->index,D_00468D30);
        int hours=(int)(seconds/3600.0f);
        int minutes=(int)(fmodf(seconds,3600.0f)/60.0f);
        func_00271448(text,D_00321720,hours,minutes);
        func_002717E0(out,text);
    }
}

extern "C" void func_0017C950(unsigned short *out) {
    func_00271730(out,func_00150630(&D_00475480,79));
    func_00271828(out,D_00321730);
    func_00271828(out,D_00321738);
}

struct SESSION_CALLBACK_REF {
    int tag; union { int n;float g;void *pv; } value;
    SESSION_CALLBACK_REF(const SESSION_CALLBACK_REF &); ~SESSION_CALLBACK_REF();
};
extern "C" SESSION_CALLBACK_REF func_002BC010(int,void *);
extern "C" void func_0012BC20(SESSION_CALLBACK_REF *);
inline SESSION_CALLBACK_REF::~SESSION_CALLBACK_REF() { func_0012BC20(this); }
extern "C" SESSION_CONTROL_NODE *func_0017C6C8(SESSION_CONTROL_DATA *);
extern "C" void func_0017CA18(unsigned short *out) {
    SESSION_CONTROL_NODE *node;
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) node=func_0017C6C8(session);
    else node=D_004BC244;
    if(node&&node->mode==2&&node->id==1815) {
        int tag=D_00475480.valueTag;
        if(tag) {
            int value;
            { SESSION_CALLBACK_REF ref=func_002BC010(tag,D_00468D30);value=ref.value.n; }
            if(value>0) {
                char text[32];
                func_00271530(text,sizeof(text),D_00321740,value);
                func_00271780(out,func_00150630(&D_00475480,494));
                func_00271828(out,D_00321748);
                func_00271828(out,text);
            }
        }
    }
}
