// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta; short pad; float *(*get)(void *); };
struct X { char pad[0xC]; struct VEntry *table; };
void func_0028FFD8(struct X *p);
float func_002A3EE8(float y, float x);
float func_0011E3B8(float g);
float func_00168108(struct X *p, float x, float y, float g)
{
    if (__builtin_fabsf(x) > 0.0f || __builtin_fabsf(y) > 0.0f) {
        float *pv;
        float a;
        func_0028FFD8(p);
        pv = p->table[36].get((char *)p + p->table[36].delta);
        a = func_002A3EE8(pv[1], pv[0]);
        return func_0011E3B8(func_002A3EE8(-x, y) + a);
    }
    return g;
}

