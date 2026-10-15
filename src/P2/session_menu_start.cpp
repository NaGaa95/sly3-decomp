// Recovered session initialization, saved selection restoration and per-state input update.
// Original range lifetimes, completion guards and switch cases are retained.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "session.h"
#include "shuffle_array.h"
struct SESSION_MENU_SOURCE { int count; const int *values; };
struct SESSION_MENU_REQUEST { void *source; int state; float elapsed; };
struct SESSION_MENU_INITIAL_FIELDS {
    char prefix[0x120]; void *source;
    char pad124[0x1B4-0x124];
    SESSION_MENU_ARRAY *records[8];
    SHUFFLE_ARRAY_FIELDS<SESSION_MENU_ARRAY *> recordsHeader;
    int previousIndex,previousState;
};
struct SESSION_MENU_DATA {
    union { SESSION_CONTROL_DATA control; SESSION_MENU_INITIAL_FIELDS init; };
    SESSION_MENU_REQUEST request;
};
struct SESSION_MENU_SAVED { char prefix[0x1488]; int state,index,selected,parentSelected; };
extern "C" SESSION_MENU_SAVED D_0036C700;
extern "C" unsigned char D_0036E740[],D_0036B118[],D_00468D30[];
extern "C" int D_003448E0,D_00344A28[];
extern "C" SESSION_MENU_SOURCE D_003449E8[];
extern "C" void func_00260930(SESSION_MENU_DATA *);
extern "C" void func_001A99D0(SESSION_MENU_REQUEST *,void *);
extern "C" void *func_001D27F0(unsigned int);
inline void *operator new(unsigned int size) { return func_001D27F0(size); }
extern "C" void func_002BDFB0(SHUFFLE_ARRAY_FIELDS<SESSION_MENU_ARRAY *> *,int,SESSION_MENU_ARRAY *const *,void *);
extern "C" int func_0025E4A0(int,void *);
extern "C" float func_0025E1F0(int,void *);
extern "C" void func_0017C328(SESSION_CONTROL_DATA *,int,int);
extern "C" void func_00185638(SESSION_MENU_SAVED *);
extern "C" void func_0017AFF0(SESSION_MENU_DATA *session) {
    func_00260930(session);
    session->init.source=D_0036E740;
    func_001A99D0(&session->request,D_0036E740);
    int last=8;
    while(last>=2&&!D_003448E0&&!func_0025E4A0(last,D_00468D30))--last;
    int count=D_00344A28[last];
    for(int i=0;i<=count;i++) {
        SESSION_MENU_SOURCE *source=&D_003449E8[i];
        session->init.records[i]=new SESSION_MENU_ARRAY(source->count,source->values,D_0036B118);
    }
    func_002BDFB0(&session->init.recordsHeader,count+1,session->init.records,D_0036B118);
    session->control.maximum=8;
    while(session->control.maximum>=2&&!D_003448E0&&func_0025E1F0(session->control.maximum,D_00468D30)==0.0f&&!func_0025E4A0(session->control.maximum-1,D_00468D30))--session->control.maximum;
    switch(D_0036C700.state) {
        case -1:
            session->control.index=session->control.maximum;
            func_0017C328(&session->control,0,-1);
            break;
        case 1:
            session->control.index=D_0036C700.index;
            func_0017C328(&session->control,D_0036C700.state,-1);
            break;
        case 6:
            session->control.index=D_0036C700.index;
            session->control.selected=D_0036C700.selected;
            func_0017C328(&session->control,D_0036C700.state,-1);
            break;
        case 11:case 16:case 21:case 27: {
            session->control.index=D_0036C700.index;
            int slot;
            switch(D_0036C700.state) {
                case 21:slot=1;break;
                case 27:slot=2;break;
                default:slot=0;break;
            }
            session->control.groups[session->control.index].slots[slot]->selected=D_0036C700.parentSelected;
            func_0017C328(&session->control,D_0036C700.state,-1);
            break;
        }
        default:break;
    }
    func_00185638(&D_0036C700);
}



struct SESSION_MENU_RANGE { float minimum,maximum; };
// Per-state session polling and input processing.
struct SESSION_MENU_INPUT { float x,y; char pad8[0x18-8]; int flags; };
struct SESSION_MENU_CLOCK { char prefix[0x44]; float delta; };
struct SESSION_MENU_TRANSFORM { float a[8]; } __attribute__((aligned(16)));
extern "C" unsigned char D_0046F550[],D_003751D0[],D_0046FBE0[],D_00389AC0[],D_004BC230[];
extern "C" SESSION_MENU_CLOCK D_0036BB98;
extern "C" int D_00344DE0[];
extern "C" SESSION_MENU_TRANSFORM D_00317FC0;
extern "C" void func_00261250(SESSION_MENU_DATA *);
extern "C" int func_0021DD30(void *);
extern "C" void func_0017BDE8(SESSION_CONTROL_DATA *);
extern "C" int func_0017BF68(SESSION_CONTROL_DATA *);
extern "C" int func_00260758(SESSION_CONTROL_DATA *,int);
#include "input_query_api.h"
extern "C" int func_001A9C38(SESSION_MENU_REQUEST *);
extern "C" int func_001A99E0(SESSION_MENU_REQUEST *);
extern "C" void func_0017C698(SESSION_CONTROL_DATA *);
extern "C" SESSION_CONTROL_OPTION *func_0017C018(SESSION_CONTROL_DATA *);
extern "C" void func_001DBD08(void *,int);
extern "C" void func_00289198(SESSION_CONTROL_GAME *,int,int,void *);
extern "C" void func_00289070(SESSION_CONTROL_GAME *,int,int,int,int);
extern "C" SESSION_CONTROL_NODE *func_0017C6C8(SESSION_CONTROL_DATA *);
extern "C" int func_0017AE78(SESSION_CONTROL_PARENT *);
extern "C" int func_0017AEB8(SESSION_CONTROL_PARENT *);
extern "C" void func_00283BB0(void *,SESSION_CONTROL_NODE *,int,int);
extern "C" SESSION_CONTROL_GAME D_00475480;
extern "C" float func_0011EE68(SESSION_MENU_RANGE *,float);
extern "C" void *func_00292034(void *,int,unsigned int);
extern "C" void func_00262990(SESSION_CONTROL_DATA *,int,const void *);
extern "C" void *func_002459F8(int);
extern "C" void func_00244F08(void *,int);
static inline void MenuInputError() { func_00244F08(func_002459F8(54),0); }
extern "C" void func_0017B298(SESSION_MENU_DATA *session) {
    func_00261250(session);
    if(func_0021DD30(D_0046F550))return;
    if(func_0021DD30(D_003751D0))return;
    if(func_0021DD30(D_0046FBE0))return;
    SESSION_CONTROL_DATA *control=&session->control;
    func_0017BDE8(control);
    int feedback=func_0017BF68(control);
    switch(control->state) {
        case 0:if(!func_00260758(control,feedback))func_0017C328(control,1,-1);break;
        case 1:if(!func_00260758(control,feedback))func_0017C328(control,2,-1);break;
        case 3:if(!func_00260758(control,900))func_0017C328(control,2,-1);break;
        case 4:if(!func_00260758(control,899))func_0017C328(control,2,-1);break;
        case 2: {
            if(func_001A7A80(session->init.source,64,0.0f)) {
                switch(control->index) {
                    case 0:func_0017C328(control,5,11);break;
                    case 2:func_00289198(&D_00475480,2,0,D_00468D30);break;
                    default:func_0017C328(control,5,6);break;
                }
            } else {
                float direction=func_001A9C38(&session->request);
                if(direction==0.0f)break;
                if((direction<0.0f&&control->index<=0)||(direction>0.0f&&control->index>=control->maximum))MenuInputError();
                else func_0017C328(control,direction<0.0f?3:4,-1);
            }
            break;
        }
        case 5:case 10:case 15:case 20:case 25:case 31:
            if(!func_00260758(control,feedback))func_0017C698(control);break;
        case 6:case 8:case 9:
            if(!func_00260758(control,feedback))func_0017C328(control,7,-1);break;
        case 7: {
            if(func_001A7A80(session->init.source,64,0.0f)) {
                SESSION_CONTROL_OPTION *option=func_0017C018(control);
                if(!option)break;
                switch(option->kind) {
                    case 0:
                        if(func_0025E1F0(control->index,D_00468D30)==0.0f)func_001DBD08(D_00389AC0,D_00344DE0[control->index]);
                        func_00289198(&D_00475480,control->index,0,D_00468D30);break;
                    case 1:
                        D_0036C700.state=6;D_0036C700.index=control->index;D_0036C700.selected=control->selected;
                        func_001DBD08(D_00389AC0,option->unknown10);
                    func_00289070(&D_00475480,0,424,0,-1);break;
                    case 3:func_0017C328(control,10,21);break;
                    case 4:func_0017C328(control,10,27);break;
                    case 2:func_0017C328(control,10,16);break;
                }
            } else if(func_001A7A80(session->init.source,16,0.0f))func_0017C328(control,10,1);
            else {
                float direction=func_001A9C38(&session->request);
                if(direction!=0.0f)func_0017C328(control,direction<0.0f?8:9,-1);
            }
            break;
        }
        case 11:case 13:case 14:
            if(!func_00260758(control,feedback))func_0017C328(control,12,-1);break;
        case 12: {
            if(func_001A7A80(session->init.source,64,0.0f)) {
                SESSION_CONTROL_NODE *node=func_0017C6C8(control);if(!node)break;
                D_0036C700.state=11;D_0036C700.index=control->index;D_0036C700.parentSelected=control->parent->selected;
                func_00283BB0(D_004BC230,node,0,-1);
            } else if(func_001A7A80(session->init.source,16,0.0f))func_0017C328(control,15,1);
            else {
                if(!control->parent)break;
                float direction=func_001A9C38(&session->request);
                if(direction==0.0f)break;
                if((direction<0.0f&&func_0017AE78(control->parent))||(direction>0.0f&&func_0017AEB8(control->parent)))func_0017C328(control,direction<0.0f?13:14,-1);
                else MenuInputError();
            }
            break;
        }
        case 16:case 18:case 19:
            if(!func_00260758(control,feedback))func_0017C328(control,17,-1);break;
        case 17: {
            if(func_001A7A80(session->init.source,64,0.0f)) {
                SESSION_CONTROL_NODE *node=func_0017C6C8(control);if(!node)break;
                D_0036C700.state=16;D_0036C700.index=control->index;D_0036C700.parentSelected=control->parent->selected;
                func_00283BB0(D_004BC230,node,0,0);
            } else if(func_001A7A80(session->init.source,128,0.0f)) {
                SESSION_CONTROL_NODE *node=func_0017C6C8(control);
                int flags=0;if(node)flags=node->flags;if(!flags)break;
                D_0036C700.state=16;D_0036C700.index=control->index;D_0036C700.parentSelected=control->parent->selected;
                func_00283BB0(D_004BC230,node,0,1);
            } else if(func_001A7A80(session->init.source,16,0.0f))func_0017C328(control,20,6);
            else {
                if(!control->parent)break;
                float direction=func_001A9C38(&session->request);
                if(direction==0.0f)break;
                if((direction<0.0f&&func_0017AE78(control->parent))||(direction>0.0f&&func_0017AEB8(control->parent)))func_0017C328(control,direction<0.0f?18:19,-1);
                else MenuInputError();
            }
            break;
        }
        case 21:case 23:case 24:
            if(!func_00260758(control,feedback))func_0017C328(control,22,-1);break;
        case 22: {
            if(func_001A7A80(session->init.source,64,0.0f))func_0017C328(control,25,26);
            else if(func_001A7A80(session->init.source,16,0.0f))func_0017C328(control,25,6);
            else {
                if(!control->parent)break;
                float direction=func_001A99E0(&session->request);
                if(direction==0.0f)break;
                if((direction<0.0f&&func_0017AE78(control->parent))||(direction>0.0f&&func_0017AEB8(control->parent)))func_0017C328(control,direction<0.0f?23:24,-1);
                else MenuInputError();
            }
            break;
        }
        case 26: {
            if(func_001A7A80(session->init.source,16,0.0f)){func_0017C328(control,21,-1);break;}
            SESSION_MENU_RANGE scaleRange={1.0f,2.0f};
            {
                SESSION_MENU_INPUT *input=(SESSION_MENU_INPUT *)session->init.source;
                if(input->flags&64)control->elapsed+=D_0036BB98.delta*0.5f;
                else if(input->flags&128)control->elapsed-=D_0036BB98.delta*0.5f;
            }
            control->elapsed=func_0011EE68(&scaleRange,control->elapsed);
            SESSION_MENU_RANGE positionRange;
            SESSION_MENU_RANGE emptyRange;func_00292034(&emptyRange,0,8);
            float inverse=1.0f/control->elapsed;
            emptyRange.minimum=inverse+(-1.0f);emptyRange.maximum=1.0f-inverse;
            positionRange=emptyRange;
            SESSION_MENU_INPUT *input=(SESSION_MENU_INPUT *)session->init.source;
            float *x=(float *)&control->field138,*y=(float *)&control->field13C;
            float delta=D_0036BB98.delta*0.5f;
            *x+=input->x*delta;
            float deltaY=D_0036BB98.delta*0.5f;
            *y+=input->y*deltaY;
            *x=func_0011EE68(&positionRange,*x);*y=func_0011EE68(&positionRange,*y);
            float px=*x*320.0f+320.0f,py=*y*(-240.0f)+240.0f;
            SESSION_MENU_TRANSFORM transform=D_00317FC0;
            transform.a[0]*=control->elapsed;transform.a[3]*=control->elapsed;
            transform.a[4]=(-px)*control->elapsed+320.0f;transform.a[5]=(-py)*control->elapsed+240.0f;
            func_00262990(control,1614,&transform);
            break;
        }
        case 27:case 29:case 30:
            if(!func_00260758(control,feedback))func_0017C328(control,28,-1);break;
        case 28: {
            if(func_001A7A80(session->init.source,64,0.0f)) {
                SESSION_CONTROL_PARENT *parent=control->parent;
                if(!parent){MenuInputError();break;}
                int selected=parent->selected;
                if(selected<0||selected>=parent->count){MenuInputError();break;}
                SESSION_CONTROL_ROW *row=&parent->rows[selected];
                if(!row||!row->available){MenuInputError();break;}
                D_0036C700.state=27;D_0036C700.index=control->index;D_0036C700.parentSelected=control->parent->selected;
                func_001DBD08(D_00389AC0,(int)row->node);
                func_00289070(&D_00475480,0,424,0,-1);
            } else if(func_001A7A80(session->init.source,16,0.0f))func_0017C328(control,31,6);
            else {
                if(!control->parent)break;
                float direction=func_001A99E0(&session->request);
                if(direction==0.0f)break;
                if((direction<0.0f&&func_0017AE78(control->parent))||(direction>0.0f&&func_0017AEB8(control->parent)))func_0017C328(control,direction<0.0f?29:30,-1);
                else MenuInputError();
            }
            break;
        }
    }
}

// Completion-query keyword used by the session option enable method at 0x17C1C0.
extern "C" const char D_003215E8[] __attribute__((section(".rodata"),aligned(8)))="is_complete";
