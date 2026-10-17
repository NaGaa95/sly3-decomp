// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Link { int key; int second; int third; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; unsigned char gap10[0x54]; struct Link *link; };
extern char D_00475480[];
void func_001C7DC8(struct Object *object);
void *func_0017E1B8(void *game,int flags,int key,void *context);
void func_002399C8(struct Object *object,void *handle,int second,int third);
void func_00239708(struct Object *object)
{
    func_001C7DC8(object);
    ((void (*)(void *))object->methods[9].method)((char *)object+object->methods[9].delta);
    if(object->link) {
        void *handle=func_0017E1B8(D_00475480,4,object->link->key,object);
        func_002399C8(object,handle,object->link->second,object->link->third);
    }
}
