// SLY3_CFLAGS: -Os -G0
struct EngineSlotOwner3 { unsigned char prefix[0x1BC]; int slot[3]; };
void func_001F3C48(void *owner);
void func_001633E0(void *owner,int value);
void func_00163388(struct EngineSlotOwner3 *owner)
{
    unsigned int i;
    func_001F3C48(owner);
    for(i=0;i<3;i++) owner->slot[i]=-1;
    func_001633E0(owner,0);
}
