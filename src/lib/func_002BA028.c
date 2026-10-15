// Reference: Sly 2 src/lib/func_002564E0.c; target Sly 3 0x002BA028.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct { int x0; int x4; } B; typedef struct { B *p0; char pad[0x20]; int x24; } A;
void func_0011AD80(void *, void *);
void func_002BA028(A *a, B *b) { a->p0 = b; func_0011AD80(&b->x4, a); a->x24 = b->x0; }
