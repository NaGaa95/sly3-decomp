// SLY3_CFLAGS: -Os -G0
struct EntryRow { int key; int value; };
extern struct EntryRow D_00321138[];
struct AddEntry { unsigned char prefix[0xE0]; int id; unsigned char padE4[0xE8-0xE4]; void *buffer; int value; };
struct AddOwner { unsigned char prefix[0x5C]; int count; struct AddEntry *entries; };
struct AddRequest { int bytes; int alignment; };
void *func_001D2670(struct AddRequest *request);
void func_00172710(struct AddOwner *owner,int id)
{
    if(owner->count<0x20) {
        struct AddEntry *entry=(struct AddEntry *)((char *)owner->entries+owner->count*0xF0);
        struct AddRequest request;
        unsigned int i;
        owner->count++;
        entry->value=-1;
        entry->id=id;
        for(i=0;i<3;i++) {
            struct EntryRow *row=&D_00321138[i];
            if(row->key==id) { entry->value=row->value; break; }
        }
        request.bytes=0x180;
        request.alignment=0x10;
        entry->buffer=func_001D2670(&request);
    }
}
