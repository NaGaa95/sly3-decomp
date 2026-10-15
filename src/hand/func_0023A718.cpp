// Retain this concrete event receiver while handling its matching event, then release it through the real virtual protocol.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Concrete table365778 slots1/2 are proven receiver-only239BB0/239BC0.
struct ReferenceDataPrefix {
    void *actor,*script;
    int reserved;
};
class ReceiverInterface:public ReferenceDataPrefix {
    public:virtual void Retain();
    virtual void Release();
};
class Receiver:public ReceiverInterface {
    public:char unknown[0x20];
    int handle;
};
class Hold {
    Receiver *pointer;
    public:Hold(Receiver *p):pointer(p) {
        p->Retain();
    }
    ~Hold() {
        pointer->Release();
    }
};
extern "C" void func_0023A640(void *receiver);
extern "C" void func_0023A428(void *receiver,int mode);
extern "C" void func_0023A718(Receiver *p,int event,int value) {
    if(event==4&&value==p->handle) {
        Hold retained(p);
        func_0023A640(p);
        func_0023A428(p,0);
    }
}
