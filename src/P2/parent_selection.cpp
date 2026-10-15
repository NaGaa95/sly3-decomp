// Recovered parent row availability, previous/next selection and active-session reset.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "session.h"
extern "C" SESSION_CONTROL_DATA *D_0047A3E8;
extern "C" void func_001C7340(SESSION_CONTROL_DATA *);

extern "C" int func_0017AE78(SESSION_CONTROL_PARENT *parent) {
    for(int i=parent->selected-1;i>=0;i--){ SESSION_CONTROL_ROW *row=parent->rows; row+=i; if(row->available)return 1; }
    return 0;
}

extern "C" int func_0017AEB8(SESSION_CONTROL_PARENT *parent) {
    for(int i=parent->selected+1;i<parent->count;i++){ SESSION_CONTROL_ROW *row=parent->rows; row+=i; if(row->available)return 1; }
    return 0;
}

extern "C" void func_0017AF08(SESSION_CONTROL_PARENT *parent) {
    for(int i=parent->selected-1;i>=0;i--) {
        SESSION_CONTROL_ROW *row=parent->rows;row+=i;
        if(row->available) {parent->selected=i;break;}
    }
}

extern "C" void func_0017AF50(SESSION_CONTROL_PARENT *parent) {
    for(int i=parent->selected+1;i<parent->count;i++) {
        SESSION_CONTROL_ROW *row=parent->rows;row+=i;
        if(row->available) {parent->selected=i;break;}
    }
}

extern "C" void func_0017AFA8(SESSION_CONTROL_DATA *session) {
    func_001C7340(session);
    session->index=-1;
    session->state=-1;
    session->nextState=-1;
    session->previousIndex=-1;
    session->previousState=-1;
    D_0047A3E8=session;
}
