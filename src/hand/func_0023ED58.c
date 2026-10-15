// Activate an attached object when its mode allows, copy the incoming 128-bit value into resource storage, and update dependent state.
// Reference algorithm: src/hand/func_001F5880.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x90]; int n90; char pad2[4]; short k; };
struct E { char pad[0x80]; qword q; };
struct P { char pad[0x48]; struct O *po; char pad2[0xD8 - 0x4C]; struct E *pe; };
void func_0028F068(struct P *, struct O *, int);
void func_0023E228(struct P *);
void func_0023ED58(struct P *p, qword q)
{
    if (p->pe) {
        struct O *po = p->po;
        if (po->n90 == 0 && po->k != 2) func_0028F068(p, po, 1);
        p->pe->q = q;
        func_0023E228(p);
    }
}
