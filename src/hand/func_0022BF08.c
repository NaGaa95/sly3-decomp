// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x2C]; void *head; int reserved; void *selected; };
void *func_00226828(void *object,void *head,int key);
void func_0022BF08(struct S *object,int key)
{
    void *selected=func_00226828(object,object->head,key);
    if(selected)object->selected=selected;
}
