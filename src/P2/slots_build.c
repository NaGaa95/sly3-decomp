// SLY3_CFLAGS: -Os -G0
struct AllocRequest { int bytes,alignment; };
struct Template { int first,second; char *name; };
struct Slot { int first,second; void *value; };
struct Table { unsigned char prefix[0x4FA8]; int count; struct Slot *slots; };
extern struct Template D_00349BD8[];
extern char D_00327EC0[];
struct Slot *func_001D2470(struct AllocRequest *request);
void *func_0021CCD0(void *name,...);
void func_0025EB00(struct Table *table)
{
    struct AllocRequest request;
    int i;
    table->count=11;
    request.bytes=0x84;
    request.alignment=0x10;
    table->slots=func_001D2470(&request);
    for(i=0;i<table->count;i++) {
        struct Slot *slot=&table->slots[i];
        struct Template *entry=&D_00349BD8[i];
        slot->first=entry->first;
        slot->second=entry->second;
        slot->value=func_0021CCD0(entry->name,D_00327EC0,0);
    }
}
