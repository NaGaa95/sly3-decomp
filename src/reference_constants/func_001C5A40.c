// Original USA entry 0x1c5a40; ordinary C reconstruction.
// Only receiver A0 is read. Absent receiver150 invokes1C5250(global475480); that callee consumes this global, deriving every other input internally. When field14C is zero and D0 is nonzero, the original47A208 word becomes1. All original loads/branches/stores match.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
extern int D_0047A208;
void func_001C5250(void *);
void func_001C5A40(char *p)  {
    if(!*(int *)(p+0x150))func_001C5250(D_00475480);
    if(!*(int *)(p+0x14C) && *(int *)(p+0xD0))D_0047A208=1;
}
