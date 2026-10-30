// SLY3_CFLAGS: -Os -G0
struct E { int value; int enabled; };
struct S { char pad[0x18]; int count; struct E entries[1]; };
void func_0024AEF8(void *, int, int, int *);

void *func_0015C420(void *result, struct S *s)
{
    int values[8];
    int n = 0;
    int i;
    for (i = 0; i < s->count; i++) {
        struct E *e = &s->entries[i];
        if (e->enabled)
            values[n++] = e->value;
    }
    func_0024AEF8(result, n, 0x2002, values);
    return result;
}
