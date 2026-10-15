// Original USA entry 0x163d30; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
void *memset(void *,int,unsigned int);
void func_00163D30(char *p,void *first,void *second)  {
    memset(p+0x1168,0,0xC);
    *(void **)(p+0x1190)=second;
    *(void **)(p+0x1164)=first;
}
