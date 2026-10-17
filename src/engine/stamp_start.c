// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
void func_002413E0(void *object,float value);
void func_002412C8(void *object,float value);
struct StartEntry { short delta,padding; void (*fn)(void *); };
struct StartChild { unsigned char prefix[0xC]; struct StartEntry *table; };
struct StartOwner { unsigned char prefix[0x13C]; struct StartChild *child; unsigned char gap140[0x144-0x140]; float stamp; };
void func_00169A30(struct StartOwner *owner)
{
    owner->stamp=D_0036BB98.t;
    if(owner->child) {
        owner->child->table[8].fn((char *)owner->child+owner->child->table[8].delta);
        func_002413E0(owner->child,1.0f);
        func_002412C8(owner->child,0.6f);
    }
}
