// Reference algorithm: src/hand/func_0022C570.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct WRE { char pad[0x70]; float x; };
struct WRE *func_0028A600(void *p, int a);
float func_0028A698(void *p)
{
    struct WRE *pwre = func_0028A600(p, 1);
    if (pwre->x == 0.0f) return 0.0f;
    return 1.0f / pwre->x;
}
