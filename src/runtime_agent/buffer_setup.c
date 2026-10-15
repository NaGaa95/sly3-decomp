// SLY3_CFLAGS: -O2 -G0
extern int *D_0034A260;
extern int D_0034A264;
extern void func_00293BC8(void *begin, void *end);

void func_00290C00(int *buffer, int count)
{
    D_0034A264 = count;
    D_0034A260 = buffer;
    buffer[count + 1] = 0;
    buffer[0] = 0;
    func_00293BC8(buffer, (char *)buffer + 3);
    buffer += count + 1;
    func_00293BC8(buffer, (char *)buffer + 3);
}
