// Reference algorithm: src/hand/func_002584A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct { unsigned char r, g, b, a; } RGBA;
typedef struct { int n; RGBA ac[1]; } LIST;
typedef struct { char pad[0xC]; int xC; char pad2[0xC]; LIST *x1C; } Y;
typedef struct { char pad[0xC0]; Y y; } T;
typedef struct { char pad[0xD4]; T *xE4; } X;
typedef struct { int cb; int align; } DESC;
int func_00119048(void *);
int func_00118FF8(void *);
int func_001190A8(void *);
void func_00236908(RGBA *);
void *func_001D2470(DESC *);

static inline int Min(int a, int b) { return a < b ? a : b; }

void func_002BD398(X *p, void *ps)
{
    int n = func_00119048(ps);
    int i;
    Y *y;
    LIST *l;
    union { DESC d; RGBA c; } u;
    if (n == 0)
        return;
    y = &p->xE4->y;
    u.d.cb = n * 4 + 4;
    u.d.align = 0x10;
    l = func_001D2470(&u.d);
    y->x1C = l;
    y->xC = func_00118FF8(ps);
    l->n = Min(n, 32);
    for (i = 0; i < n; i++) {
        *(int *)&u.c = func_001190A8(ps);
        func_00236908(&u.c);
        if (i < l->n)
            l->ac[i] = u.c;
    }
}
