// Recovered session feedback, option lookup, cyclic previous selection and enable checks.
// Original OR bounds and frame/reference lifetimes are retained.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "session.h"
extern "C" SESSION_CONTROL_MENU *func_0017BFF0(SESSION_CONTROL_DATA *);
extern "C" void func_0017C078(SESSION_CONTROL_DATA *);
extern "C" void func_0017C118(SESSION_CONTROL_DATA *);
extern "C" int func_0017C1C0(SESSION_CONTROL_DATA *,SESSION_CONTROL_OPTION *);
extern "C" SESSION_CONTROL_NODE *func_0017C6C8(SESSION_CONTROL_DATA *);
extern "C" int func_002835D0(SESSION_CONTROL_NODE *);
extern "C" void func_00262450(SESSION_CONTROL_DATA *,int);
extern "C" void func_00262990(SESSION_CONTROL_DATA *,int,const char *);
extern "C" void func_0016F2B0(void *,int);
extern "C" void func_0017AF08(SESSION_CONTROL_PARENT *);
extern "C" void func_0017AF50(SESSION_CONTROL_PARENT *);
extern "C" int func_0017AE78(SESSION_CONTROL_PARENT *);
extern "C" int func_0017AEB8(SESSION_CONTROL_PARENT *);
extern "C" int func_0017BF68(SESSION_CONTROL_DATA *);
extern "C" unsigned char D_00375290[];
extern "C" const char D_00317FC0[];
extern "C" void func_001CFE08(void *);

class CFrame { int m_a[4]; public: CFrame(); ~CFrame(); };
struct SESSION_CHOICE_REF {
    int tag; union {int n;float g;void *pv;} value;
    SESSION_CHOICE_REF(const SESSION_CHOICE_REF &); ~SESSION_CHOICE_REF();
};
extern "C" SESSION_CHOICE_REF func_002BC010(int,void *);
extern "C" void func_0012BC20(SESSION_CHOICE_REF *);
inline SESSION_CHOICE_REF::~SESSION_CHOICE_REF() {func_0012BC20(this);}
extern "C" int func_0021CDA8(int,const char *,int);
extern "C" int func_0025E4A0(int,void *);
extern "C" const char D_003215E8[];
extern "C" unsigned char D_00468D30[];
extern "C" int D_003448E0;
extern "C" const int D_00344E08[],D_00344E88[],D_00344EB0[],D_00344ED8[];
extern "C" SESSION_CONTROL_MENU D_00344D98[];

extern "C" int func_0017BF68(SESSION_CONTROL_DATA *session) {
    switch(session->state) {
        case 6:return D_00344E88[session->index];
        case 7:return D_00344EB0[session->index];
        case 10:return D_00344ED8[session->index];
        default:return D_00344E08[session->state];
    }
}

extern "C" SESSION_CONTROL_MENU *func_0017BFF0(SESSION_CONTROL_DATA *session) {
    unsigned int index=session->index;
    if(index>=9)return 0;
    return &D_00344D98[index];
}

extern "C" SESSION_CONTROL_OPTION *func_0017C018(SESSION_CONTROL_DATA *session) {
SESSION_CONTROL_MENU *menu=func_0017BFF0(session);
    if(!menu)return 0;
    int selected=session->selected;
    if(selected<0&&selected>=menu->count)return 0;
    return &menu->options[selected];
}

extern "C" void func_0017C118(SESSION_CONTROL_DATA *session) {
    SESSION_CONTROL_MENU *menu=func_0017BFF0(session);
    if(menu) {
        int start=session->selected;
        for(;;) {
            int next=session->selected;
            next-=1;
            next=next+menu->count;
            session->selected=next;
            int selected=next%menu->count;
            session->selected=selected;
            if(start==selected||!(selected>=0||selected<menu->count))break;
            if(func_0017C1C0(session,&menu->options[selected]))break;
        }
    }
}

static inline int ChoiceValue(int tag) { int value; { SESSION_CHOICE_REF ref=func_002BC010(tag,D_00468D30);value=ref.value.n; } return value; }
extern "C" int func_0017C1C0(SESSION_CONTROL_DATA *session,SESSION_CONTROL_OPTION *option) {
    if(D_003448E0)return 1;
    switch(option->kind) {
        case 0:
            if(session->index==1||session->index==8) {
                if(func_0025E4A0(session->index,D_00468D30))return 0;
            }
            break;
        case 1:
            if(option->scriptTag) {
                CFrame frame;
                int tag=func_0021CDA8(option->scriptTag,D_003215E8,0);
                if(!ChoiceValue(tag))return 0;
            }
            break;
        case 2: {SESSION_CONTROL_PARENT *parent=session->groups[session->index].slots[0];return parent&&parent->enabled;}
        case 3: {SESSION_CONTROL_PARENT *parent=session->groups[session->index].slots[1];return parent&&parent->enabled;}
        case 4: {SESSION_CONTROL_PARENT *parent=session->groups[session->index].slots[2];return parent&&parent->enabled;}
        default:break;
    }
    return 1;
}
