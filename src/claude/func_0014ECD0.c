// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
int func_00185770(void *a, void *b);

int func_0014ECD0(char *p)
{
    int n;
    if (*(int *)(p + 0x1AC)) {
        n = *(int *)(p + 0x194);
    } else {
        n = func_00185770(D_0036C700, p);
        switch (n) {
        case 0:
            n = *(int *)(p + 0x194);
            break;
        case 24: case 25: case 26: case 28: case 29: case 30: case 31:
            n = -1;
            break;
        }
    }
    switch (n) {
    case 0x316: n = 0x313; break;
    case 0x317: n = 0x314; break;
    case 0x318: n = 0x315; break;
    }
    return n;
}
