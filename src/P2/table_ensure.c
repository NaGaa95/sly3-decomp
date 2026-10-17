// SLY3_CFLAGS: -Os -G0
struct AllocRequest { int bytes, alignment; };
struct Slots { unsigned char prefix[0x17C4]; int *table; };
int *func_001D2470(struct AllocRequest *request);
void func_00257F50(struct Slots *slots)
{
    if(!slots->table) {
        struct AllocRequest request;
        int i;
        request.bytes=0x18;
        request.alignment=0x10;
        slots->table=func_001D2470(&request);
        for(i=0;i<6;i++)
            slots->table[i]=-1;
    }
}
