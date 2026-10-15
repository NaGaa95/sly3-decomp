// Reference: Sly 2 src/lib/_alarm_bind.c; target Sly 3 0x00295C18.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
unsigned int isceSifSendCmd(unsigned int, void *, int, void *, void *, int);
int _alarm_bind(int id, unsigned short t, int a, void *rd)
{
    return isceSifSendCmd(0x80000008, rd, 0x40, 0, 0, 0) ? 0 : 0x800;
}
