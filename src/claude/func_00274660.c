// SLY3_CFLAGS: -Os -G0
// Five small accessors that config/functions.csv currently lumps into func_00274660.
struct T { char pad[0x70]; float x70; float x74; float x78; };
struct S { char pad[0x114]; struct T *x114; };
void func_00274660(struct S *p)
{
    p->x114 = 0;
}
int func_00274668(struct S *p)
{
    return *(int *)p->x114;
}
struct T *func_00274678(struct S *p)
{
    return p->x114;
}
void func_00274680(struct S *p, float f)
{
    struct T *t = p->x114;
    t->x74 = f;
    t->x70 = f;
    p->x114->x78 = 1.0f;
}
float func_002746A0(struct S *p)
{
    return p->x114->x70;
}
