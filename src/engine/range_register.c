// SLY3_CFLAGS: -Os -G0
struct RegEntry { short delta,padding; void (*fn)(void *); };
struct RegObject { unsigned char prefix[0xC]; struct RegEntry *table; void *owner; unsigned char gap14[0x88-0x14]; int slot88; int slot8C; unsigned char gap90[0xA8-0x90]; int slotA8; int slotAC; };
void func_001C7DC8(void *object);
void func_00147E08(void *owner,int a,int b,void *c,int d,int e,int f,void *g);
void func_00139848(struct RegObject *object)
{
    func_001C7DC8(object);
    object->table[9].fn((char *)object+object->table[9].delta);
    func_00147E08(object->owner,0xC,2,&object->slot8C,0,0,0,&object->slot88);
    func_00147E08(object->owner,0xC,2,&object->slotAC,0,0,0,&object->slotA8);
}
