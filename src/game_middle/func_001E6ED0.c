// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Classifies which way round a closed path a pair of positions lies (same routine as Sly 2 func_001BCCE0): projects both
// parameters onto the path (trying both probe modes), measures the arc between them and decides between the two walking
// directions (1 / 2), or fails with 4. Mode 2 stretches the "short way" threshold by 1.2, mode 1 shrinks it by 0.8.
float func_0022DFD8(void *path);
int func_001E7100(void *path, void *context, float t, float range, float *out, int mode);
int func_001E6CB8(void *path, void *context, float from, float to, int direction);

int func_001E6ED0(void *path, void *context, float *pt, int mode, float t)
{
    float at[2];
    float end, arc, scale;
    int isShort, forward, backward;

    if (!func_001E7100(path, context, t, func_0022DFD8(path) * 0.5f, &at[0], 0) &&
        !func_001E7100(path, context, t, func_0022DFD8(path) * 0.5f, &at[0], 1))
        return 4;
    t = at[0];
    if (!func_001E7100(path, context, *pt, func_0022DFD8(path) * 0.5f, &at[1], 0) &&
        !func_001E7100(path, context, *pt, func_0022DFD8(path) * 0.5f, &at[1], 1))
        return 4;
    end = at[1];
    *pt = end;
    arc = end - t;
    if (arc < 0.0f)
        arc += func_0022DFD8(path);
    switch (mode) {
    case 2: scale = 1.2f; break;
    case 1: scale = 0.8f; break;
    default: scale = 1.0f; break;
    }
    isShort = (arc < func_0022DFD8(path) * scale * 0.5f) ? 1 : 0;
    forward = func_001E6CB8(path, context, t, end, 1);
    backward = func_001E6CB8(path, context, t, end, 0);
    if (backward < forward)
        return 1;
    if (forward < backward)
        return 2;
    if (forward != 2)
        return isShort ? 2 : 1;
    return 4;
}
