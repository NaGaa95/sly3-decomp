// SLY3_CFLAGS: -Os -G0
struct EngineNotifyWorld { unsigned char prefix[0x10D0]; void *controller; };
struct EngineNotifyItem { unsigned char prefix[0x14]; void *subject; };
struct EngineNotifySubject { unsigned char prefix[0x10]; struct EngineNotifyWorld *world; unsigned char gap[0x30-0x14]; struct EngineNotifyItem *item; };
extern unsigned char D_0036C700[];
void func_0016C980(void *subject);
void func_001854C8(void *context,int event,void *owner);
void func_001703C8(void *controller,void *subject,int mode);
void func_0016D038(struct EngineNotifySubject *subject)
{
    void *controller;
    void *request;
    func_0016C980(subject);
    func_001854C8(D_0036C700,15,subject->world);
    request=subject->item->subject;
    controller=subject->world->controller;
    func_001703C8(controller,request,2);
}
