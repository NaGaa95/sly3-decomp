// Reference algorithm: src/hand/func_001FAF70.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct MSG { int cb; int nKind; } MSG;
void *func_001D2538(MSG *pmsg);
struct E { int n; float a; float b; float c; int d; char unknown_tail[4]; };
struct E *func_00244B68(void)
{
    MSG msg;
    struct E *pe;
    msg.cb = sizeof(struct E);
    msg.nKind = 0x10;
    pe = func_001D2538(&msg);
    pe->n = -1;
    pe->a = 300.0f;
    pe->b = 3000.0f;
    pe->c = 1.0f;
    return pe;
}
