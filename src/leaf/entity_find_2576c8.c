// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void *); };
struct Entity { unsigned char prefix[0xC]; struct Method *methods; unsigned char gap10[8]; int kind; unsigned char gap1C[0x24]; int key; };
extern char D_00475480[];
int func_0017E208(void *game,int flags,int key,void *owner,int limit,struct Entity **items);
struct Entity *func_00150690(int kindKey,void *owner,int kind,int extra);
void func_00258FD0(struct Entity *entity);
struct Entity *func_002576C8(void *owner,int key)
{
    struct Entity *items[32];
    int count=func_0017E208(D_00475480,1,0x95,owner,0x20,items);
    int i;
    for(i=0;i<count;i++) {
        struct Entity *candidate=items[i];
        if(candidate->kind==0x325&&candidate->key==key)
            return candidate;
    }
    {
        struct Entity *entity=func_00150690(0x95,owner,0x325,-1);
        struct Method *method;
        entity->key=key;
        func_00258FD0(entity);
        method=&entity->methods[9];
        method->method((char *)entity+method->delta);
        return entity;
    }
}
