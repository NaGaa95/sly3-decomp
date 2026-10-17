// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int PathPacked __attribute__((mode(TI)));
typedef union { PathPacked raw; float scalar; } PathScalarCarrier;
void func_001F32E8(void *path, float parameter, int reverse, void *output_frame);
void func_0022E330(void *path, void *point, void *direction, float parameter);

static inline PathPacked path_offset(PathPacked position, PathPacked axis, float scale)
{
    PathScalarCarrier carrier;
    PathPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
            : "=j"(result) : "j"(position), "j"(axis), "j"(carrier.raw));
    return result;
}

void func_001F37D8(void *path, int unused, PathPacked *output, float parameter)
{
    PathPacked frame[3];
    PathPacked point[1];
    func_001F32E8(path, parameter, 1, frame);
    func_0022E330(path, point, 0, parameter);
    if (output)
        *output = path_offset(point[0], frame[0], -50.0f);
}
