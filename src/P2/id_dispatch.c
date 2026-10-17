// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
static inline void CallObject(struct Object *object,int slot)
{
    ((void (*)(void *))object->methods[slot].method)((char *)object+object->methods[slot].delta);
}
void func_00260F18(struct Object *object,int a,int b,int c);
void func_00260EC8(struct Object *object,int id)
{
    if(id==-1)
        CallObject(object,56);
    else
        func_00260F18(object,-1,id,-1);
}
