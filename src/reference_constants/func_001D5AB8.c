// Original USA entry 0x1d5ab8; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
void func_0023C0B8(void *,void *);
void func_0028F068(void *,void *,int);
void func_001D69D8(void *);
void func_001D5AB8(char *p,void *stream)  {
    char *data;
    func_0023C0B8(p,stream);
    func_0028F068(p,*(void **)(p+0x48),1);
    data=*(char **)(p+0x48)+0xF0;
    *(int *)(data+4)=0;
    *(int *)(data+8)=0;
    *(int *)data=0;
    *(int *)(p+0x1B4)=*(short *)(*(char **)(p+0x4C)+0x98);
    func_001D69D8(p);
}
