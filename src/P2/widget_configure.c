// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Widget { unsigned char prefix[0xC]; struct Method *methods; unsigned char gap10[0x20]; int field30; struct Widget *linked; };
static inline void CallWidget(struct Widget *widget,int slot)
{
    ((void (*)(void *))widget->methods[slot].method)((char *)widget+widget->methods[slot].delta);
}
static inline void CallWidgetInt(struct Widget *widget,int slot,int value)
{
    ((void (*)(void *,int))widget->methods[slot].method)((char *)widget+widget->methods[slot].delta,value);
}
int func_0021DD30(struct Widget *widget);
void func_00222FF0(struct Widget *widget,int first,int value,struct Widget *linked)
{
    if(func_0021DD30(widget))
        CallWidget(widget,11);
    widget->field30=first;
    widget->linked=linked;
    CallWidgetInt(widget,10,value);
}
