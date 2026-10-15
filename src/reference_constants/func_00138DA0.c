// Original USA entry 0x138da0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
void func_0012F288(void *);
void func_00138DA0(char *p)  {
    if(*(int *)(p+0x20))  {
        *(int *)(*(char **)(*(char **)(p+8)+0xA8)+0xA4)=*(int *)(p+0x20);
        *(void **)(*(char **)(*(char **)(p+8)+0xA8)+0xA8)=*(char **)(p+0x24)+0x1C;
    }
    else func_0012F288(p);
}
