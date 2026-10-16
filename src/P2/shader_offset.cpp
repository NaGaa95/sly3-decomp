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

typedef char CheckScrollCycle70[sizeof(ShaderScrollCycle) == 0x70 ? 1 : -1];
extern "C" int func_0011AEF8(void *);
extern "C" void func_00237168(ShaderScrollCycle *);

static inline int QuantizeShaderOffset(float offset)
{
    return (int)(offset * 4096.0f + 0.5f) & 0xFFF;
}

extern "C" void func_00237298(ShaderScrollCycle *state, float u, float v)
{
    if (func_0011AEF8(&state->users)) return;
    state->u = u;
    state->v = v;
    int packedU = QuantizeShaderOffset(u);
    int packedV = QuantizeShaderOffset(v);
    if (state->packedU == packedU && state->packedV == packedV) return;
    state->packedU = packedU;
    state->packedV = packedV;
    func_00237168(state);
}
