// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Resource { unsigned char prefix[0xF0]; float weight; };
struct Owner { unsigned char prefix[0x4308]; int count; struct Resource *items[10]; void *first; unsigned char gap4338[4]; void *second; void *third; };
void *func_0017E1B8(void *game,int flags,int key_word,void *owner);
int func_0017E208(void *game,int flags,int key_word,void *owner,int capacity,struct Resource **output);
void func_0025CD00(struct Owner *owner)
{
    struct Resource *found[0x100];
    int total;
    int index;
    owner->first=func_0017E1B8(owner,0x405,0x425,0);
    owner->second=func_0017E1B8(owner,0x405,0x42A,0);
    owner->third=func_0017E1B8(owner,0x405,0x42B,0);
    total=func_0017E208(owner,0x405,0x9E,0,0x100,found);
    owner->count=0;
    for(index=0;index<total;index++) {
        struct Resource *resource=found[index];
        if(resource->weight<=0.0f)
            continue;
        owner->items[owner->count++]=resource;
    }
}
