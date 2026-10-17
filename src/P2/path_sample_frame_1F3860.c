// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int PathPacked __attribute__((mode(TI)));
typedef union { PathPacked raw; float scalar; } PathScalarCarrier;
float func_0022FC20(void *path, float seed, float limit);
void func_001F32E8(void *path, float parameter, int reverse, void *output_frame);
void func_0022E330(void *path, void *point, void *direction, float parameter);
float func_0011E940(float low, float high);
PathPacked func_0011FD70(float heading, float radius, float height);

static inline PathPacked path_offset(PathPacked position, PathPacked axis, float scale)
{
    PathScalarCarrier carrier;
    PathPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
            : "=j"(result) : "j"(position), "j"(axis), "j"(carrier.raw));
    return result;
}

static inline PathPacked path_rotate(PathPacked vector, PathPacked row0, PathPacked row1, PathPacked row2)
{
    PathPacked result;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(result) : "j"(vector), "j"(row0), "j"(row1), "j"(row2));
    return result;
}

void func_001F3860(void *path, PathPacked *position, PathPacked *direction, float seed)
{
    PathPacked point[1];
    PathPacked frame[3];
    float parameter, sign, magnitude;
    PathPacked rotated;
    parameter = func_0022FC20(path, seed, 150.0f);
    func_001F32E8(path, parameter, 1, frame);
    func_0022E330(path, point, 0, parameter);
    sign = func_0011E940(-1.0f, 1.0f);
    magnitude = __builtin_fabsf(sign);
    rotated = path_rotate(func_0011FD70(sign * magnitude * 1.8f, -1.0f, 0.0f), frame[0], frame[1], frame[2]);
    {
        PathPacked origin = point[0];
        magnitude = magnitude * func_0011E940(0.0f, 25.0f);
        *position = path_offset(origin, rotated, magnitude);
    }
    *direction = rotated;
}
