// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct QuadView { unsigned char opaque[0x1E60]; Quad value; };

void func_001AFBE0(void *receiver, Quad value)
{
    ((struct QuadView *)receiver)->value = value;
}
