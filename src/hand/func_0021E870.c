// Set current or pending animation selection and blend duration according to the transition state; the supported GNU assembler profile preserves the complete original 20-byte switch table.
// Reference algorithm: src/hand/func_001DA4B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
typedef struct {
    char pad[0x10];
    int x10;
    int pad14;
    int x18;
    float x1C;
    int x20;
    float x24;
} OBJ;
void func_0021E930(OBJ *, int);
void func_0021E980(OBJ *, int);
void func_0021E870(OBJ *p, int n, float g)
{
    if (n == -1) {
        func_0021E930(p, -1);
        return;
    }
    switch (p->x10) {
    case 1:
        func_0021E980(p, -1);
    case 0:
    case 3:
        p->x18 = n;
        p->x1C = g;
        func_0021E980(p, 1);
        break;
    case 2:
        if (p->x18 == n) {
            p->x1C = g;
            break;
        }
    case 4:
        p->x20 = n;
        p->x24 = g;
        break;
    }
}
