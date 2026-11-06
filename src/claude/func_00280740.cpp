// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef unsigned long u64;
struct O { char pad[0x120]; u64 lo120 : 63; u64 f120 : 1; union { struct { u64 f128 : 1; u64 hi128 : 63; }; u64 x128; }; };
struct N { int x0; O *o; int x8; N *next; };
extern "C" {
extern char D_00475480[];
void func_002811F0(O *o, N *n);
void func_002811C8(O *o, N *n);
void func_00281178(void *g, N *n);
}
extern "C" void func_00280740(void *p, N **pp)
{
    N *n = *pp;
    N *done = 0;
    while (n) {
        O *o = n->o;
        N *next = n->next;
        if (o->f120 != ((unsigned int)*(u64 *)&o->x128 & 1)) {
            if (o->f120)
                func_002811F0(o, n);
            else
                func_002811C8(o, n);
        }
        if (n->o->f128) {
            pp = &n->next;
        } else {
            *pp = next;
            n->next = done;
            done = n;
        }
        {
            O *q = n->o;
            q->f128 = 0;
            q->f120 = 0;
        }
        n = next;
    }
    func_00281178(D_00475480, done);
}
