// Select each event descriptor's desired entry from its key and fallback flags; deactivate the old entry and activate the new one when the selection changes.
// Reference algorithm: src/hand/func_001DB390.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct {
    int key;
    int a;
    int b;
    int c;
    int cur;
    int pad[2];
    int flags;
} E;
typedef struct {
    char pad0[0x34];
    void *x24;
    char pad28[0x48 - 0x28];
    int key;
    int n;
    E *ae;
} OBJ;
void func_00262280(void *, int);
void func_00262450(void *, int);
void func_0021F948(OBJ *p, int key)
{
    int i;
    p->key = key;
    for (i = 0; i < p->n; i++) {
        E *e = &p->ae[i];
        int v;
        if (e->key == key)
            v = e->c;
        else if (e->flags & 4)
            v = e->b;
        else if (e->flags & 2)
            v = e->a;
        else
            v = -1;
        if (v != e->cur) {
            if (p->x24 && e->cur != -1)
                func_00262280(p->x24, e->cur);
            e->cur = v;
            if (p->x24 && v != -1)
                func_00262450(p->x24, v);
        }
    }
}
