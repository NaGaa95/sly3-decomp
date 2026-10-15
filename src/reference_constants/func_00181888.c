// Original USA entry 0x181888; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Text  {
    int encoding,unused;
    union  {
        unsigned char *bytes;
        unsigned short *units;
    } buffer;
};
void func_00181888(struct Text *p,unsigned short character,int index)  {
    switch(p->encoding)  {
        case 0:p->buffer.bytes[index]=character;
        return;
        case 1:p->buffer.units[index]=character;
        return;
    }
}
