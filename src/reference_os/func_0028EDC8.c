// Sly 2 reference: src/hand/func_00230100.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct N { char pad[0x10]; struct N *next; int x14; VT *vt; } N;
typedef struct S { char pad[0x90]; N *first; } S;
void func_0028B1B0(void *, S *);

#define VCALL(o, k) ((void (*)(void *))(o)->vt[k].pfn)((char *)(o) + (o)->vt[k].d)

void func_0028EDC8(void *ctx, S *s, N *n)
{
    N *head = s->first;
    N **pp = &s->first;
    N *e;
    for (e = head; e; e = e->next) {
        if (e == n) {
            *pp = e->next;
            if (s->first != head) {
                func_0028B1B0(ctx, s);
                VCALL(head, 2);
                if (s->first)
                    VCALL(s->first, 1);
            } else if (head) {
                VCALL(head, 3);
            }
            return;
        }
        pp = &e->next;
    }
}
