// Reference algorithm: src/hand/func_001F37C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Q { char pad[0x108]; char dl[1]; };
struct O { char pad[0x10]; struct Q *pq; char pad2[0x20 - 0x14]; char sub[1]; };
struct E { char pad[0xDC]; struct O *po; };
struct P { char pad[0xD8]; struct E *pe; };
int func_0011B0C0(void *, void *);
void func_0011B028(void *, void *);
void func_0011AF60(void *, void *);
void func_001EDD18(struct Q *, void *);
void func_0023C750(struct P *p, struct Q *q)
{
    struct O *o = p->pe->po;
    struct Q *old = o->pq;
    if (old == q) return;
    if (old) {
        if (func_0011B0C0(old->dl, o)) func_0011B028(old->dl, o);
    }
    if (q) {
        if (!func_0011B0C0(q->dl, o)) {
            func_0011AF60(q->dl, o);
            func_001EDD18(q, o->sub);
        }
    }
    o->pq = q;
}
