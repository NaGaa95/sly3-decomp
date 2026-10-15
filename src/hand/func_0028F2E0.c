// Advance the attached object's state according to its state identifier and secondary mode, preserving the complete relocated dispatch table.
// Reference algorithm: src/hand/func_00230630.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct S { char pad[0x98]; short k; short x9A; } S;
void func_0028F068(void *, S *, int);

void func_0028F2E0(void *p, S *s)
{
    switch (s->k) {
    case 8:
    case 10:
        if (s->x9A == 2)
            func_0028F068(p, s, 11);
        else if (s->x9A == 1)
            func_0028F068(p, s, 7);
        break;
    case 12:
        if (s->x9A == 2)
            func_0028F068(p, s, 0xD);
        break;
    case 19:
        if (s->x9A == 2)
            func_0028F068(p, s, 0x14);
        break;
    case 1:
        func_0028F068(p, s, 3);
        break;
    }
}
