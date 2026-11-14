// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Update the orientation sent to the handle using the tilt toward the target.
typedef int qword __attribute__((mode(TI)));
union Vector { qword q; float lane[4]; };
struct Matrix { qword row[4]; };
struct Entry { short adjustment, pad; void *method; };
struct Actor { char pad[0xC]; Entry *vtable; };
struct State {
    char pad0[0x10];
    Actor *actor;
    char pad14[0x24];
    Actor *target;
    char pad3C[0xB4];
    void *handle;
    char padF4[0xC];
    float x, y;
};

extern "C" {
void func_0012F410(void *);
void func_0012F3D0(void *);
void func_00120528(qword, float *, float *);
void func_0012F4F8(void *, qword);
}

static inline Matrix *Transform(Actor *actor)
{
    Entry &slot = actor->vtable[36];
    return ((Matrix *(*)(void *))slot.method)((char *)actor + slot.adjustment);
}
static inline qword Subtract(const qword &a, const qword &b)
{
    qword result;
    asm("vsub.xyzw %0,%0,%1" : "=j"(result) : "j"(b), "0V"(a));
    return result;
}
extern "C" void func_001352F8(State *state)
{
    Vector out, angles;
    struct { float tilt; Vector target; } facing;
    if (!state->handle)
        return;
    if (!state->target) {
        func_0012F410(state->handle);
        return;
    }
    func_0012F3D0(state->handle);
    facing.target.q = Transform(state->target)->row[3];
    func_00120528(Subtract(facing.target.q, Transform(state->actor)->row[3]), 0, &facing.tilt);
    qword zero = 0;
    // The operand keeps the tilt in f1 while GCC loads the other two angles.
    register float tilt asm("$f1") = facing.tilt;
    asm("" : "+f"(tilt));
    angles.q = zero;
    float x = state->x;
    float y = state->y;
    angles.lane[0] = x;
    angles.lane[1] = y;
    angles.lane[2] = tilt;
    out = angles;
    func_0012F4F8(state->handle, out.q);
}
