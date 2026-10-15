// Original USA entry 0x173448; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
int func_001731B0(void *);
void func_00173228(void *);
void func_00173448(char *p)  {
    if(++*(int *)(p+0x64)==1 && func_001731B0(p))func_00173228(p);
}
