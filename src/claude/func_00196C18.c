// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 func_00170548 (goto loop); the do { } while (0) wrapper gives the loop-align nop without loop.c moving the exit block.
struct B { int n0; int n4; struct B *next; };
struct S { char pad0[4]; int n4; char pad8[4]; struct B *ap[8]; };
int func_00196B18(int n);
void func_00196B88(struct S *p);
int func_00196C18(struct S *p, int cb)
{
    unsigned int i;
    int old;
    struct B *pb;
    i = func_00196B18(cb - 1) + 1;
    do {
    goto test;
loop:
    pb = p->ap[i];
    if (pb) {
        old = pb->n0;
        pb->n0 = old + cb;
        if (pb->n0 == pb->n4) {
            p->ap[i] = pb->next;
        } else {
            unsigned int j = func_00196B18(pb->n4 - pb->n0);
            if (j != i) {
                p->ap[i] = pb->next;
                pb->next = p->ap[j];
                p->ap[j] = pb;
            }
        }
        goto done;
    }
    i++;
test:
    if (i < 8) goto loop;
    } while (0);
    if (((p->n4 + cb) & ~0x7F) != (p->n4 & ~0x7F)) func_00196B88(p);
    old = p->n4;
    p->n4 = old + cb;
done:
    return old;
}
