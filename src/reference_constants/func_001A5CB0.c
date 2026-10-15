// Reference algorithm: src/hand/func_001C2048.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x120]; int a; char pad2[0x2c]; int b; };
void func_0012F378(struct S *p);
void func_001A5CB0(struct S *p) { func_0012F378(p); *(int *)((char *)p + 0x1C) = *(int *)(*(char **)((char *)p + 8) + 0xA8); }
