// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Dispatch the stored member-function callback (cleared before it runs; a null or the default one reports event 0xB first);
// without a callback, pick between a virtual notification on the owner, the default handler and a 1.0 blend request.
struct VTE { short d; short pad; void (*pfn)(void *); };
struct Owner { char pad[0xC]; VTE *vt; };
struct Q { char pad[0x128]; unsigned long flags; };
struct P { char pad[0x14]; Q *x14; };
class Obj;
typedef void (Obj::*PMF)();
class Obj {
public:
    Owner *owner;
    int mode;
    int x8;
    PMF cb;
    P *x14;
    void Update() __asm__("func_001C2E78");
    void Default() __asm__("func_001C2FE8");
};
extern "C" void func_00292034(void *p, int v, int n);
extern "C" void func_001854C8(void *p, int a, void *o);
extern "C" int func_0013B500(Q *q, int n);
extern "C" void func_001B7268(void *p, int a, float f, int b, int c);
extern "C" char D_0036C700[];
void Obj::Update()
{
    PMF f = cb;
    func_00292034(&cb, 0, 8);
    if (f == (PMF)0 || f == &Obj::Default)
        func_001854C8(D_0036C700, 0xB, owner);
    if (f) {
        (this->*f)();
    } else if ((unsigned)(mode - 9) < 5) {
        VTE *e = &owner->vt[0x67];
        e->pfn((char *)owner + e->d);
    } else if (func_0013B500(x14->x14, 0x2F) && (x14->x14->flags & 2)) {
        Default();
    } else {
        func_001B7268((char *)owner + 0x320, 0xB, 1.0f, 0, 0);
    }
}
