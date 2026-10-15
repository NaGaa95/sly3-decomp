// Release the old embedded resource record, update the timestamp from the original float fields, bind the new record, and forward all explicit object/resource/index/vector arguments.
// Reference algorithm: src/hand/func_0020AB68.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
typedef int qword __attribute__((mode(TI)));
extern struct { float t; float dt; } D_0036BB98;
extern float D_00327490;
struct C { char pad[0xC]; int fl; };
struct O { char pad[0x50]; float f60; float f64; char pad2[0xB0 - 0x58]; struct C record; };
struct S { char pad[0x107C]; struct O *po; float t; };
void func_00254E18(struct C *pc);
float func_0011E940(float a, float b);
void func_00254D38(struct C *pc, struct S *p, int fl, float g);
void func_00256828(struct S *p, struct O *po, void *node, qword v)
{
    if (p->po) {
        float t;
        func_00254E18(&p->po->record);
        t = D_0036BB98.t;
        t += func_0011E940(p->po->f60, p->po->f64);
        p->po = 0;
        p->t = t;
    }
    p->po = po;
    if (po) {
        func_00254D38(&po->record, p, po->record.fl | 1, 0.0f);
        p->t = D_00327490;
    }
    func_002568E8(p, po, node, v);
}
