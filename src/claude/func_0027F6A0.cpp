// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
class FRAME {
public:
    int x;
    FRAME();
    ~FRAME();
};
struct ALLOCREQ { int cb; int align; };
struct S { char pad[0x23C]; int n23C; int *a240; };
extern "C" {
int *func_001D2608(ALLOCREQ *req, void *src);
void func_0015D510(S *p);
void func_00257A70(int v, S *p);
}
static inline void Init(ALLOCREQ *r, int cb, int align)
{
    r->cb = cb;
    r->align = align;
}
extern "C" void func_0027F6A0(S *p)
{
    FRAME frame;
    int i = 0;
    int n = p->n23C;
    int *old;
    {
        ALLOCREQ req;
        Init(&req, n * 4, 16);
        old = func_001D2608(&req, p->a240);
    }
    func_0015D510(p);
    for (; i < p->n23C; i++) {
        int v = p->a240[i];
        int j;
        for (j = 0; j < n; j++)
            if (old[j] == v)
                goto next;
        func_00257A70(v, p);
    next:;
    }
}
