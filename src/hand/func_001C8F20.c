// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct O { char pad[0x10]; struct O *x10; };
int func_001C8F20(struct O *a, struct O *b)
{
    while (a) {
        if (a == b) break;
        a = a->x10;
    }
    return a != 0;
}
