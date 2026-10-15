// Reference algorithm: src/hand/func_001E6340.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Q { char pad[0x4C]; int st; };
struct S { char pad[0x16C]; struct Q *pq; };
void func_0022FF98(struct Q *q);
void func_00230C70(struct Q *q);
void func_001C81B8(struct S *p);
void func_0022DCC8(struct S *p)
{
    if (p->pq) {
        switch (p->pq->st) {
        case 0:
        case 3:
            func_0022FF98(p->pq);
            break;
        case 1:
        case 2:
            func_00230C70(p->pq);
            break;
        }
    } else {
        func_001C81B8(p);
    }
}
