// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int StateVector __attribute__((mode(TI)));
struct TrackedRecord {
    unsigned char prefix[0x1C];
    float time;
};
struct VectorApply {
    unsigned char prefix[0x1014];
    int busy;
    unsigned char gap1018[0x101C - 0x1018];
    void *path;
    float parameter;
    unsigned char gap1024[0x113C - 0x1024];
    TrackedRecord *tracked;
    unsigned char gap1140[0x19E0 - 0x1140];
    int state;
    unsigned char gap19E4[0x1A60 - 0x19E4];
    StateVector offset;
};
extern "C" {
StateVector func_001B2070(void *receiver);
void func_001B2138(void *receiver, StateVector vector);
void func_0022E330(void *path, void *point, void *direction, float parameter);
void func_00154FD8(void *receiver);
}
static inline StateVector AddStateVectors(StateVector a, StateVector b)
{
    StateVector sum;
    asm("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a), "j"(b));
    return sum;
}
extern "C" void func_001AB858(VectorApply *apply)
{
    switch (apply->state) {
    case 4:
        func_001B2138(apply, AddStateVectors(func_001B2070(apply), apply->offset));
        break;
    case 0x11:
        func_001B2138(apply, func_001B2070(apply));
        break;
    case 9:
        if (!apply->busy && apply->tracked) {
            if (apply->tracked->time < 0.35f) {
                StateVector sample;
                func_0022E330(apply->path, &sample, 0, apply->parameter);
                func_001B2138(apply, sample);
            }
        }
        break;
    }
    func_00154FD8(apply);
}
