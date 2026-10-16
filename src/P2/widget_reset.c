// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Widget { unsigned char prefix[0xC]; struct Method *methods; unsigned char gap10[0x24]; struct Widget *linked; unsigned char gap38[0x18]; int field50; int field54; };
static inline void CallWidget(struct Widget *widget,int slot)
{
    ((void (*)(void *))widget->methods[slot].method)((char *)widget+widget->methods[slot].delta);
}
static inline void CallWidgetInt(struct Widget *widget,int slot,int value)
{
    ((void (*)(void *,int))widget->methods[slot].method)((char *)widget+widget->methods[slot].delta,value);
}
int func_00221AC0(struct Widget *widget);
void func_00221FA8(struct Widget *widget);
void func_00221AC8(struct Widget *widget,int value)
{
    widget->field54=1;
    widget->field50=0;
    if(widget->linked) {
        CallWidgetInt(widget,10,value);
        CallWidget(widget->linked,56);
        if(func_00221AC0(widget))
            func_00221FA8(widget);
    }
}
