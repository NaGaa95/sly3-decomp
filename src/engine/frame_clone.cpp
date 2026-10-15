// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
EvalFrame *func_002BA9A8();
void func_002BABA8(EvalFrame *,int flags);
void func_002BACE0(void *,int flags);
}
struct CloneBinding { unsigned references; };
struct FrameReference {
    EvalFrame *value;
    void operator=(EvalFrame *frame) __asm__("func_002BAA50");
};
struct BindingReference {
    CloneBinding *value;
    void operator=(CloneBinding *binding) __asm__("func_002BAED0");
};
struct CloneFrameView {
    unsigned references;
    unsigned word4;
    FrameReference parent;
    BindingReference bindings;
};
struct FrameOwner {
    EvalFrame *value;
    void Set(EvalFrame *frame) __asm__("func_002BAB88");
    ~FrameOwner() {
        EvalFrame *frame=value;
        if(frame && --((CloneFrameView *)frame)->references==0)
            func_002BABA8(frame,3);
    }
};
struct BindingOwner {
    CloneBinding *value;
    BindingOwner(const BindingOwner &);
    ~BindingOwner() {
        CloneBinding *binding=value;
        if(binding && --binding->references==0)
            func_002BACE0(binding,3);
    }
};
extern "C" BindingOwner func_0012CD10(CloneBinding *,EvalFrame *,void *context);
extern "C" FrameOwner *func_00129BE0(FrameOwner *result,EvalFrame *source,void *context) {
    FrameOwner frame;
    frame.Set(func_002BA9A8());
    ((CloneFrameView *)frame.value)->parent=((CloneFrameView *)source)->parent.value;
    if(((CloneFrameView *)source)->bindings.value) {
        EvalFrame *destination=frame.value;
        BindingOwner bindings=func_0012CD10(((CloneFrameView *)source)->bindings.value,destination,context);
        ((CloneFrameView *)destination)->bindings=bindings.value;
    }
    result->Set(frame.value);
    return result;
}
