// SLY3_CFLAGS: -Os -G0
// Store a 0x20-byte value into the slot of entry id that matches the entry kind (4: +0x14, 7: +0x18, 1: +0x20),
// allocating the slot on first use (allocator vtable slot 1).
typedef int qword __attribute__((mode(TI)));
struct V { qword a, b; };
struct VTE { short delta; short pad; struct V *(*pfn)(void *, int, int); };
struct ALLOC { struct VTE *vt; };
struct E { int n0; int kind; int n8; int id; int n10; struct V *pv14; struct V *pv18; int n1C; struct V *pv20; char pad24[0xC]; };
struct S { char pad[0x40]; int ce; struct E *ae; char pad48[0xB4 - 0x48]; struct ALLOC *palloc; };
static inline struct V *Alloc(struct S *p)
{
    struct ALLOC *pa = p->palloc;
    return pa->vt[1].pfn((char *)pa + pa->vt[1].delta, 0x20, 0x29);
}
void func_00262990(struct S *p, int id, struct V *pv)
{
    int i;
    for (i = 1; i <= p->ce; i++) {
        struct E *pe = &p->ae[i];
        switch (pe->kind) {
        case 4:
            if (pe->id == id) {
                if (!pe->pv14)
                    pe->pv14 = Alloc(p);
                *pe->pv14 = *pv;
                return;
            }
            break;
        case 7:
            if (pe->id == id) {
                if (!pe->pv18)
                    pe->pv18 = Alloc(p);
                *pe->pv18 = *pv;
                return;
            }
            break;
        case 1:
            if (pe->id == id) {
                if (!pe->pv20)
                    pe->pv20 = Alloc(p);
                *pe->pv20 = *pv;
                return;
            }
            break;
        }
    }
}
