// Recovered queued-session selection polling and replacement.
// Virtual base and derived storage preserve the original historical C++ ABI.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "session.h"
#include "shuffle_array.h"
struct SESSION_PREVIOUS_FIELDS { char prefix[0x1D4]; SHUFFLE_ARRAY_FIELDS<SESSION_MENU_ARRAY *> array; };
extern "C" int func_00260758(SESSION_CONTROL_DATA *,int);
extern "C" void func_00262280(SESSION_CONTROL_DATA *,int);
extern "C" float func_002617F0(SESSION_CONTROL_DATA *,int);
extern "C" SESSION_MENU_ARRAY *func_002B4FF0(SHUFFLE_ARRAY_FIELDS<SESSION_MENU_ARRAY *> *);
extern "C" void func_00262450(SESSION_CONTROL_DATA *,int);
extern "C" void func_0017BDE8(SESSION_CONTROL_DATA *session) {
    if(session->previousState!=-1&&!func_00260758(session,session->previousState)) {
        func_00262280(session,session->previousState);session->previousState=-1;
    }
    if(session->previousIndex!=-1&&!func_00260758(session,session->previousIndex)) {
        func_00262280(session,session->previousIndex);session->previousIndex=-1;
    }
    switch(session->state) {
      case 2:case 3:case 4:
        if(session->previousState==-1&&session->previousIndex!=-1&&func_002617F0(session,session->previousIndex)<=0.5f) {
            session->previousState=session->previousIndex;session->previousIndex=-1;
        }
        if(session->previousIndex==-1) {
            SESSION_MENU_ARRAY *array=func_002B4FF0(&((SESSION_PREVIOUS_FIELDS *)session)->array);
            int selection=array->Choice();
            session->previousIndex=selection;
            func_00262450(session,selection);
            if(!func_00260758(session,session->previousIndex))session->previousIndex=-1;
        }
        break;
      default:
        if(session->previousState!=-1) {func_00262280(session,session->previousState);session->previousState=-1;}
        if(session->previousIndex!=-1) {func_00262280(session,session->previousIndex);session->previousIndex=-1;}
        break;
    }
}
