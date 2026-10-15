// Reference algorithm: src/hand/func_00156EB8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; char pad[0x58 - 0x10]; struct O *pNext; };
struct S { int a[3]; struct VTE *vt; char pad[0xD0 - 0x10]; unsigned int c; struct O *ao[8]; };
extern struct O *D_00479C04;
void func_001C8168(struct S *p);
void func_00174048(struct S *p, int f);
int func_00174238(struct S *p, struct O *o);
void func_00174120(struct S *p)
{
    struct O *o;
    func_001C8168(p);
    func_00174048(p, 0);
    for (o = D_00479C04; o; o = o->pNext) {
        int i;
        for (i = 0; i < (int)p->c; i++)
            if (o == p->ao[i])
                break;
        if (i < (int)p->c)
            continue;
        if (!func_00174238(p, o))
            continue;
        if (p->c < 8) {
            struct VTE *e = &o->vt[1];
            e->pfn((char *)o + e->d);
            p->ao[p->c++] = o;
            e = &p->vt[3];
            e->pfn((char *)p + e->d, 5, 0, 0, 0, 0);
        }
        return;
    }
}
