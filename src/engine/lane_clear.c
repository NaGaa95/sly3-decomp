// SLY3_CFLAGS: -Os -G0
struct EngineLaneSlot { int key; unsigned char gap4[0xC]; int field10; unsigned char gap14[8]; int field1C; unsigned char gap20[8]; };
struct EngineLaneInfo { unsigned char gap0[8]; int field8; unsigned char gap0C[8]; };
struct EngineLaneOwner { unsigned char prefix[0x38]; int count; struct EngineLaneInfo *lanes; struct EngineLaneSlot *slots; };
void func_0018FF30(struct EngineLaneOwner *owner,int key)
{
    int i;
    for(i=0;i<owner->count;i++) {
        struct EngineLaneSlot *slot=&owner->slots[i];
        struct EngineLaneInfo *lane=&owner->lanes[i];
        if(slot->key==key) {
            slot->field1C=0;
            slot->field10=0;
            lane->field8=0;
        }
    }
}
