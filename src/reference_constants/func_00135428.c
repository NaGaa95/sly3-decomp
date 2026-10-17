// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_00238978(void *);
void func_002541F8(void *, void *);
void func_001355C8(void *, int);
void func_00135428(void *p) { func_00238978(p); func_002541F8(*(void **)((char *)p + 0x10), *(void **)((char *)p + 0x30)); func_001355C8(p, 0); }
