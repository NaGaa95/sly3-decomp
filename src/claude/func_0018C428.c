// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Lane helpers in the style of src/hand/func_00120528.c.
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
void func_0018C220(int item, float x, float y, float a, float b);
void func_0018C428(int limit, int *items, int count, qword pos)
{
    float x = GetX(pos) * 320.0f + 320.0f - 175.0f;
    float y = GetY(pos) * -240.0f + 240.0f;
    int i;
    for (i = 0; i < count; i++) {
        if (i < limit) {
            func_0018C220(items[i], x, y, 0.3f, 0.6f);
        }
        x += 75.0f;
    }
}
