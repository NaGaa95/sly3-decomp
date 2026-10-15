// Recovered session node kind, labels, description, value and mission callbacks.
// Provisional structure names; accessed fields and original strides are proven.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "game_text.h"
#include "session.h"
struct SESSION_NODE_REF {
    int tag; union { int n;float g;void *pv; } value;
    SESSION_NODE_REF(const SESSION_NODE_REF &); ~SESSION_NODE_REF();
};
extern "C" SESSION_NODE_REF func_002BC010(int,void *);
extern "C" void func_0012BC20(SESSION_NODE_REF *);
inline SESSION_NODE_REF::~SESSION_NODE_REF() { func_0012BC20(this); }
extern "C" SESSION_CONTROL_GAME D_00475480;
extern "C" SESSION_CONTROL_NODE *D_004BC244;
extern "C" unsigned char D_00468D30[];
extern "C" SESSION_CONTROL_NODE *func_0017C6C8(SESSION_CONTROL_DATA *);
extern "C" int func_00222410(int);
extern "C" void func_00271530(char *,unsigned int,const char *,...);
extern "C" int func_002835D0(SESSION_CONTROL_NODE *);
extern "C" void func_00283620(SESSION_CONTROL_NODE *,char *,float);
extern "C" const char D_00321730[],D_00321740[],D_00321748[],D_00321750[],D_00321758[],D_00321760[];

extern "C" void func_0017CB18(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) {
        SESSION_CONTROL_NODE *node=func_0017C6C8(session);
        if(node) {
            if(node->mode==1)func_00271780(out,func_00150630(&D_00475480,127));
            else if(node->mode==0)func_00271780(out,func_00150630(&D_00475480,130));
        }
    }
}

extern "C" void func_0017CBB0(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) {
        SESSION_CONTROL_NODE *node=func_0017C6C8(session);
        if(node&&node->nameId!=-1)func_00271730(out,func_00150630(&D_00475480,node->nameId));
    }
}

extern "C" void func_0017CC20(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) {
        SESSION_CONTROL_NODE *node=func_0017C6C8(session);
        if(node)func_00271730(out,func_00150630(&D_00475480,node->descriptionId));
    }
}

extern "C" void func_0017CC88(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) {
        SESSION_CONTROL_NODE *node=func_0017C6C8(session);
        if(node) {
            if(node->mode==1) {
                func_00271780(out,func_00150630(&D_00475480,128));
                func_00271828(out,D_00321730);func_00271828(out,D_00321750);
                if(node->flags) {
                    func_00271828(out,D_00321758);
                    func_00271780(out,func_00150630(&D_00475480,129));
                    func_00271828(out,D_00321760);
                }
            } else {
                func_00271780(out,func_00150630(&D_00475480,131));
                func_00271828(out,D_00321730);func_00271828(out,D_00321750);
                if(node->flags) {
                    func_00271828(out,D_00321758);
                    func_00271780(out,func_00150630(&D_00475480,132));
                    func_00271828(out,D_00321760);
                }
            }
        }
    }
}

extern "C" void func_0017CDE0(unsigned short *out) {
    SESSION_CONTROL_NODE *node;
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session)node=func_0017C6C8(session);else node=D_004BC244;
    if(node) {
        if(node->mode==2&&node->id==1815&&D_00475480.valueTag) {
            int tag=D_00475480.valueTag;
            int value;
                { SESSION_NODE_REF ref=func_002BC010(tag,D_00468D30);value=ref.value.n; }
                if(value>0) {
                    char text[32];func_00271530(text,sizeof(text),D_00321740,value);
                    func_00271780(out,func_00150630(&D_00475480,494));
                    func_00271828(out,D_00321748);func_00271828(out,text);
                }
        } else if(node->mode==0&&func_002835D0(node)) {
            if(node->valueA0!=0.0f) {
                char text[32];func_00283620(node,text,node->valueA4);
                func_00271780(out,func_00150630(&D_00475480,494));
                func_00271828(out,D_00321748);func_00271828(out,text);
            } else if(node->value9C!=0.0f) {
                char text[32];func_00283620(node,text,node->valueA4);
                func_00271780(out,func_00150630(&D_00475480,498));
                func_00271828(out,D_00321748);func_00271828(out,text);
            }
        }
    }
}

extern "C" void func_0017CFC0(unsigned short *out) {
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) {
        int index=session->index;
        if((unsigned int)index<9)func_00271730(out,func_00150630(&D_00475480,func_00222410(index)));
    }
}
