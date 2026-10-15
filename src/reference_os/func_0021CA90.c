// Sly 2 reference: src/hand/func_001D8690.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { unsigned int h; char *s; void *pv; struct E *next; };
struct S { struct E *ap[0x35]; int c; struct E *ae; };
unsigned int func_0021CA40(char *s);
void func_0021CA90(struct S *p, char *s, void *pv) {
    unsigned int h = func_0021CA40(s);
    unsigned int ih = h % 0x35;
    struct E *pe = &p->ae[p->c - 1];
    p->c--;
    pe->s = s;
    pe->pv = pv;
    pe->h = h;
    pe->next = p->ap[ih];
    p->ap[ih] = pe;
}
