// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/func_0014E078.c.
typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x100]; int k; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct CM { char pad[0xC]; struct VEntry *table; };
extern char D_00475480[];
int func_0017E208(void *g, int a, int b, int c, int n, struct O **ap);
void func_0027E988(struct O *po, qword pos);
void func_00292540(void *base, int n, int cb, int (*cmp)(const void *, const void *));
int func_00166C70(const void *a, const void *b);
void func_00166DC8(struct CM *p, struct O *po);
void func_00166CE8(struct CM *p)
{
    struct O *apo[32];
    qword pos = *(qword *)((char *)p->table[36].get((char *)p + p->table[36].delta) + 0x30);
    int n = func_0017E208(D_00475480, 0x105, 7, 0, 0x20, apo);
    int i;
    for (i = 0; i < n; i++)
        func_0027E988(apo[i], pos);
    func_00292540(apo, n, 4, func_00166C70);
    if (n > 0 && apo[0]->k == 1)
        func_00166DC8(p, apo[0]);
}
