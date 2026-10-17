// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_001FC8F8(struct S *p, void *owner);
void func_001FECC0(void *, int);
void func_001FEB30(struct S *p, void *owner) { func_001FC8F8(p, owner); func_001FECC0(p, 1); }
