// SLY3_CFLAGS: -Os -G0
struct SlotRequest { unsigned char prefix[0x164]; int mask; };
void *func_00185720(char *table,struct SlotRequest *request)
{
    int bits=request->mask;
    unsigned int index=0;
    while(bits && (bits&1)==0) { index++; bits>>=1; }
    if(bits!=1 || index>=7) return 0;
    return table+0x18+index*16;
}
