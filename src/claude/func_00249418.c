// SLY3_CFLAGS: -Os -G0
// Base update, then reset the value at +0xF8 to 1250 (store done through a flag test).
struct S { char pad[0xF8]; float g; };
void func_001C7DC8(struct S *p);
void func_00249418(struct S *p)
{
    int f;
    func_001C7DC8(p);
    f = p->g == 1250.0f;
    if (f)
        p->g = 1250.0f;
}
