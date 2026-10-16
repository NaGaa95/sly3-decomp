// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CallbackReceiver {
    virtual void callbackAnchor();
};
typedef void (CallbackReceiver::*CleanupMethod)(void *);
struct CleanupDescriptor {
    char unaccessed[0x60];
    CleanupMethod method;
};
struct CallbackChild {
    char unaccessed[0xF0];
    CleanupDescriptor *descriptor;
    CallbackReceiver *receiver;
    void *payload;
};
struct S;
extern "C" void func_0020BD70(S *child);

extern "C" void func_0020DE48(CallbackChild *child)
{
    CleanupMethod method=child->descriptor->method;
    (child->receiver->*method)(child->payload);
    func_0020BD70((S *)child);
}
