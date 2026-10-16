// SLY3_CFLAGS: -Os -G0
struct EngineValidateEntry { short delta,padding; void (*fn)(void *,int,int,int,int,int); };
struct EngineValidateOwner { unsigned char prefix[0xC]; struct EngineValidateEntry *table; };
int func_0021F410(int id);
void func_001548E8(void *owner,int index,int value);
void func_001546B8(struct EngineValidateOwner *owner)
{
    int i;
    owner->table[3].fn((char *)owner+owner->table[3].delta,0x1D,0,0,0,0);
    for(i=0;i<3;i++) {
        if(!func_0021F410(*(int *)((char *)owner+0x1250+i*12))) func_001548E8(owner,i,0);
    }
}
