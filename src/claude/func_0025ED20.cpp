// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Build an entry from two id lists; REQs live in an Alloc() inline so the 2nd reuses the freed CRef temp slot.
struct CRef;
extern "C" void func_0012BC20(CRef *pr);
struct CRef {
    short tag;
    short cref;
    int val;
    CRef(const CRef &r);
    ~CRef() { func_0012BC20(this); }
};
struct L;
struct REQ { int cb; int align; };
struct ENT { void *p0; int n4; void *p8; void *pC; };
struct P { char pad[0x4FB0]; ENT *aent; };
extern "C" {
extern int D_00349CA8[];
extern char g_heapSw[];
CRef func_0024B330(L *list, int tag, int unused, int *count, int *dest);
void func_0025EC70(P *p);
void *func_001D24D0(REQ *preq, void *pv);
void *func_001D27F0(unsigned int size);
void *func_002BFA48(void *storage, int count, const int *ids, void *heap);
void func_0025ED20(P *p, int i, L *a, L *b);
}
static inline void *Alloc(int cb, void *pv) { REQ r; r.cb = cb; r.align = 0x10; return func_001D24D0(&r, pv); }
void func_0025ED20(P *p, int i, L *a, L *b)
{
    int ab[8], bb[8];
    int c0, c1;
    func_0025EC70(p);
    ENT *e = &p->aent[i];
    func_0024B330(a, 0x10, 8, &c0, ab);
    func_0024B330(b, 0x10, 8, &c1, bb);
    e->n4 = c0;
    e->p8 = Alloc(c0 * 4, ab);
    e->pC = Alloc(c1 * 4, bb);
    e->p0 = func_002BFA48(func_001D27F0(0x14), e->n4, D_00349CA8, g_heapSw);
}
