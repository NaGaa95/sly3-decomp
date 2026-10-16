// SLY3_CFLAGS: -Os -G0
struct EngineNotifyEntry { short delta,padding; void (*fn)(void *); };
struct EngineNotifyChild { unsigned char prefix[0xC]; struct EngineNotifyEntry *table; };
struct EngineNotifyWorld { unsigned char prefix[0x10D0]; void *controller; unsigned char gap[0x1148-0x10D4]; struct EngineNotifyChild *child; };
struct EngineNotifyItem { unsigned char prefix[0x14]; void *subject; };
struct EngineNotifySubject { unsigned char prefix[0x10]; struct EngineNotifyWorld *world; unsigned char gap[0x30-0x14]; struct EngineNotifyItem *item; };
extern unsigned char D_0036C700[];
void func_0016C980(void *subject);
void func_001854C8(void *context,int event,void *owner);
void func_001703C8(void *controller,void *subject,int mode);
void func_0016D0C0(struct EngineNotifySubject *subject)
{
    void *controller;
    void *request;
    func_0016C980(subject);
    func_001854C8(D_0036C700,15,subject->world);
    request=subject->item->subject;
    controller=subject->world->controller;
    func_001703C8(controller,request,2);
    if(subject->world->child) subject->world->child->table[8].fn((char *)subject->world->child+subject->world->child->table[8].delta);
}
