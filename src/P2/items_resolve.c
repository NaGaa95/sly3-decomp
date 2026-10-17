// SLY3_CFLAGS: -Os -G0
struct Item { int key; void *object; unsigned char gap8[0x18]; };
struct Resolver { unsigned char prefix[0x174]; int count; struct Item *items; };
extern char D_00475480[];
void func_0023C580(struct Resolver *resolver);
void *func_0017E1B8(void *game,int flags,int key,void *context);
int func_0013B500(void *object,int kind);
void func_002804E8(struct Resolver *resolver)
{
    int i;
    func_0023C580(resolver);
    for(i=0;i<resolver->count;i++) {
        void *object=func_0017E1B8(D_00475480,4,resolver->items[i].key,resolver);
        if(object&&func_0013B500(object,0x13))
            resolver->items[i].object=object;
    }
}
