// SLY3_CFLAGS: -Os -G0
extern int *D_0034A260;
extern int D_0034A264;
extern int D_0034A2D8;
extern char D_0032A130[];
extern char D_004C4180[];
extern int func_00296108(void *object);
extern void func_00293CF8(void *begin, void *end);
extern void func_00293920(int command);
extern int func_00271388(const char *message);

int func_00290B30(void)
{
    int *buffer;
    int *current;
    unsigned int first;
    int count;
    if (D_0034A260 == 0)
        return 1;
    if (func_00296108(D_004C4180) != 0)
        return 0;
    buffer = D_0034A260;
    count = D_0034A264;
    func_00293CF8(buffer, (void *)(count * 4 + (unsigned int)buffer + 8));
    current = D_0034A260;
    first = current[0];
    if (first == 0xFFFFFFFFU && current[D_0034A264 + 1] == first) {
        func_00293920(0);
        D_0034A260 = 0;
        return 1;
    }
    if (D_0034A2D8 == 0)
        func_00271388(D_0032A130);
    return 0;
}
