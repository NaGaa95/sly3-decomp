// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
void func_0024F470(void *p, void *a, void *b, qword v);
struct B { unsigned char pad[0x2F]; unsigned long flags : 8; };

void func_00153438(char *p, void *a, struct B *b, qword pos)
{
    qword d;
    if (!(b->flags & 1)) {
        func_001B7268(p + 0x320, 0, 0, 0, 1.0f);
        return;
    }
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(*(qword *)(p + 0x1120)));
    func_0024F470(p, a, b, d);
}
