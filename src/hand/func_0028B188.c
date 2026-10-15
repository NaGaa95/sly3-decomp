// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x80]; int a; float b; int *pa; float *pb; };
void func_0028B188(void *q, struct S *p)
{
    p->b = 1.0f;
    p->a = 0;
    p->pa = &p->a;
    p->pb = &p->b;
}
