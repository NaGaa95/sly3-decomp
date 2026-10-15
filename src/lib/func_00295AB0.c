// Reference: Sly 2 src/lib/_alarm_rdata.c; target Sly 3 0x00295AB0.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
unsigned int isceSifSendCmd(unsigned int, void *, int, void *, void *, int);
typedef struct { int pad[9]; void *src; void *dest; int size; } RDATA;
int _alarm_rdata(int id, unsigned short t, int a, RDATA *rd)
{
    return isceSifSendCmd(0x80000008, rd, 0x40, rd->src, rd->dest, rd->size) ? 0 : 0x800;
}
