// Original USA entry 0x1304e8; ordinary C reconstruction.
// Receiver A0 supplies owner4 and destination8; float1C and the complete128-bit vectors20/30 are stored at destination A8/C0/D0, followed by16-bit type9A=2. Both explicit pointer inputs to 28B188 are forwarded from the original receiver fields.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_0028B188(void *,void *);
void func_001304E8(char *p)  {
    *(float *)(*(char **)(p+8)+0xA8)=*(float *)(p+0x1C);
    *(qword *)(*(char **)(p+8)+0xC0)=*(qword *)(p+0x20);
    *(qword *)(*(char **)(p+8)+0xD0)=*(qword *)(p+0x30);
    *(short *)(*(char **)(p+8)+0x9A)=2;
    func_0028B188(*(void **)(p+4),*(void **)(p+8));
}
