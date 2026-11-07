// SLY3_CFLAGS: -Os -G0
// Write a scalar into the record at (+0xD8)->+0xDC, creating it if needed (func_00241B60).
struct Record { float f0, f4, f8, fC; };
struct Actor;
struct Record *func_00241B60(struct Actor *a);
void func_00241C70(struct Actor *a, float g)
{
    struct Record *r = func_00241B60(a);
    if (r)
        r->fC = g;
}
