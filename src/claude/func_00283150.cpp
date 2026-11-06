// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class FRAME {
public:
    int x;
    FRAME();
    ~FRAME();
};
struct ALLOCREQ { int cb; int align; };
struct KEY;
struct S { char pad[0xA4]; float fA4; char keyA8[0x10]; int xB8; void *xBC; };
extern "C" {
extern unsigned char D_00468D30[];
void *func_001D25B0(ALLOCREQ *req);
void *func_001D24D0(ALLOCREQ *req, void *prev);
void func_001C7D98(S *p, void *pbis);
void func_00119830(void *pbis);
CRef *func_002BC010(CRef *result, KEY *key, unsigned char *context);
}
static inline void Init(ALLOCREQ *r, int cb)
{
    r->cb = cb;
    r->align = 16;
}
extern "C" void func_00283150(S *p, void *pbis)
{
    FRAME frame;
    {
        ALLOCREQ req;
        Init(&req, 0x600);
        p->xBC = func_001D25B0(&req);
    }
    func_001C7D98(p, pbis);
    {
        ALLOCREQ req;
        Init(&req, p->xB8 * 0x18);
        p->xBC = func_001D24D0(&req, p->xBC);
    }
    func_00119830(pbis);
    {
        CRef c;
        func_002BC010(&c, (KEY *)p->keyA8, D_00468D30);
        float g = c.payload.real;
        func_0012BC20(&c);
        p->fA4 = g;
    }
}
