// SLY3_CFLAGS: -Os -G0
typedef struct {
    char pad[0x10];
    int id;
    char pad2[0xDC - 0x14];
    int c;
    int a[1];
} S;
int func_00169150(S *p, int id)
{
    int i;
    if (p->id == -1 || id == -1 || p->id == id) {
        return 1;
    }
    for (i = 0; i < p->c; i++) {
        if (p->a[i] == id) {
            return 1;
        }
    }
    return 0;
}
