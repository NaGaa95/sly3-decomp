// SLY3_CFLAGS: -Os -G0
struct Link { unsigned char prefix[0x18]; int id; };
struct Slot { unsigned char prefix[0x48]; int id; unsigned char gap4C[0x14]; int key; int value; };
struct Record { unsigned char prefix[0x18]; int key; unsigned char gap1C[0x50]; struct Link *link; };
struct Owner { unsigned char prefix[0x14]; struct Slot *slot; };
struct Current { unsigned char prefix[0x58]; struct Record *record; };
extern struct Current *D_004794C4;
int func_002852B0(struct Owner *owner);
int func_002845B0(struct Owner *owner,struct Record *record,int value)
{
    struct Slot *slot;
    if(!func_002852B0(owner)||!record->link)
        return 0;
    slot=owner->slot;
    if(record->link->id!=slot->id||slot->value!=value)
        return 0;
    if(slot->key!=-1) {
        if(slot->key==record->key)
            return 1;
    } else if(D_004794C4->record==record)
        return 1;
    return 0;
}
