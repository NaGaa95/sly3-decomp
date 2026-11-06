// SLY3_CFLAGS: -Os -G0
// Two functions that config/functions.csv currently lumps into func_0028A818.
struct E { char pad[0x10]; int x10; char pad2[0x6C]; };
struct S { char pad[0x60]; struct E e[17]; char pad2[0x938 - 0x60 - 17 * 0x80]; int f[18]; };
void func_0028A818(struct S *p, struct E *e)
{
    e->x10 = 0;
    p->f[e - p->e] = 0;
}
struct F { float x0; float x4; };
int func_0028A838(struct F *a, struct F *b)
{
    return (a->x0 - b->x4 < 0.0f) ? -1 : 1;
}
