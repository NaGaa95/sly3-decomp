// Recovered session transition, pending-state pop and selected-node lookup.
// Switch cases and accessed fields are decoded from original code and tables.
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
extern "C" void func_0017C328(SESSION_CONTROL_DATA *session,int state,int nextState) {
    if(session->state==state)return;
    switch(session->state) {
        case 0:func_001CFE08(D_00375290);break;
        case 5:
            if(state==6) {
                session->selected=func_0017BFF0(session)->count-1;
                func_0017C078(session);
            }
            break;
        case 3:--session->index;break;
        case 4:++session->index;break;
        case 26:func_00262990(session,1614,D_00317FC0);break;
        case 25:if(state==26)break;
        case 15:case 20:case 31:session->parent=0;break;
        default:break;
    }
    session->nextState=nextState;
    session->state=state;
    switch(state) {
        case 1:case 2:func_00262450(session,898);break;
        case 3:func_00262450(session,900);break;
        case 4:func_00262450(session,899);break;
        case 6:case 7:case 10: {
            SESSION_CONTROL_MENU *menu=func_0017BFF0(session);
            if(menu) {
                for(int i=0;i<menu->count;i++) {
                    SESSION_CONTROL_OPTION *option=&menu->options[i];
                    if(func_0017C1C0(session,option)) {
                        func_00262450(session,session->selected==i?option->selectedId:option->labelId);
                    } else func_00262450(session,option->disabledId);
                }
            }
            break;
        }
        case 8:func_0017C118(session);break;
        case 9:func_0017C078(session);break;
        case 17: {
            SESSION_CONTROL_NODE *node=func_0017C6C8(session);
            if(node&&node->mode==0)func_00262450(session,func_002835D0(node)?1493:1494);
            break;
        }
        case 11:case 16:case 21:case 27: {
            int slot;
            switch(session->state) {
                case 27:slot=2;break;
                case 21:slot=1;break;
                default:slot=0;break;
            }
            SESSION_CONTROL_PARENT *parent=session->groups[session->index].slots[slot];
            session->parent=parent;
            func_0016F2B0(parent->textOwner,parent->textId);
            goto update_parent_labels;
        }
        case 13:case 18:case 23:case 29:
            func_0017AF08(session->parent);
            goto update_parent_labels;
        case 14:case 19:case 24:case 30:
            func_0017AF50(session->parent);
        update_parent_labels:
            func_00262450(session,func_0017AE78(session->parent)?1615:1616);
            func_00262450(session,func_0017AEB8(session->parent)?1617:1618);
            break;
        case 26: {
            SESSION_CONTROL_PARENT *parent=session->parent;
            if(parent&&parent->itemOwner) {
                func_0016F2B0(parent->itemOwner,(int)parent->rows[parent->selected].node);
                session->field138=0;
                session->elapsed=1.0f;
                session->field13C=0;
            }
            break;
        }
        default:break;
    }
    int feedback=func_0017BF68(session);
    if(feedback!=-1&&session->feedback!=feedback) {
        SESSION_CONTROL_VTABLE *vtable=session->vtable;
        vtable->SetFeedback((char *)session+vtable->delta,feedback);
    }
}

extern "C" void func_0017C698(SESSION_CONTROL_DATA *session) {
    int state=session->nextState;
    session->nextState=-1;
    func_0017C328(session,state,-1);
}

extern "C" SESSION_CONTROL_NODE *func_0017C6C8(SESSION_CONTROL_DATA *session) {
SESSION_CONTROL_PARENT *parent=session->parent;
    if(!parent)return 0;
    if(parent->mode)return 0;
    if(session->index!=parent->index)return 0;
    int selected=parent->selected;
    if(selected<0)return 0;
    return selected<parent->count?parent->rows[selected].node:0;
}

extern "C" { extern const char D_00321718[] __attribute__((section(".rodata"))) = "%d%%"; }
