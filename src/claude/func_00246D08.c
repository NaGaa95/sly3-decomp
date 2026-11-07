// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CLOCK { float t, dt; };
extern struct CLOCK D_0036BB98;
struct P {
    char pad0[0x140];
    float a140[8][4];
    float f1C0;
    float a1C4[4];
    float target1D4;
    char pad1D8[0x200 - 0x1D8];
    unsigned long time200, previous208;
};
extern struct P D_00474FF0;
void func_002906B8(int);
void func_00291CA8(int, int, int, int, int, int, int);
unsigned long func_001655B0(struct CLOCK *);
void func_00246D08(void) {
    int i, j;
    unsigned long t;
    func_002906B8(2);
    func_00291CA8(0x524B5553, 0, 0, 0, 0, 0, 0);
    D_00474FF0.f1C0 = 1.0f;
    for (i = 0; i < 4; i++) {
        D_00474FF0.a1C4[i] = 1.0f;
        for (j = 0; j < 8; j++) D_00474FF0.a140[j][i] = 1.0f;
    }
    D_00474FF0.target1D4 = 3.40282346638528859812e+38f;
    t = func_001655B0(&D_0036BB98);
    D_00474FF0.time200 = t;
    D_00474FF0.previous208 = t;
}
