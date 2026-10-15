// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ShaderScrollUsers { void *first, *last; int memberOffset; };
struct ShaderScrollCycle {
    char prefix[0x24];
    short packedU, packedV;
    int unused28;
    float u, v;
    char pad34[4];
    ShaderScrollUsers users;
    char pad44[0x50 - 0x44];
    float uSpeed, vSpeed, uPeriod, vPeriod, uScale, vScale;
    char opaqueTail[8];
};
struct ShaderScrollClock { float current, delta; };
typedef char CheckScrollCycle70[sizeof(ShaderScrollCycle) == 0x70 ? 1 : -1];
extern "C" ShaderScrollClock D_0036BB98;
extern "C" int func_0011AEF8(void *);
extern "C" float func_0011EDB8(float, float);
extern "C" void func_00237298(ShaderScrollCycle *, float, float);

extern "C" void func_00237CA0(ShaderScrollCycle *state)
{
    float u, v;
    if (func_0011AEF8(&state->users)) return;
    u = func_0011EDB8(state->u + state->uSpeed * state->uScale * D_0036BB98.delta,
        state->uPeriod);
    v = func_0011EDB8(state->v + state->vSpeed * state->vScale * D_0036BB98.delta,
        state->vPeriod);
    func_00237298(state, u, v);
}
