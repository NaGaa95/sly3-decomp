// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
float func_0022E058(void *path, float parameter);
void func_0022E330(void *path, void *point, void *direction, float parameter);
int func_001ED170(void *context, qword point, int flags);

int func_001E7100(void *path, void *context, float *output, float center, int flags, float range)
{
    qword backward, forward;
    float offset;
    float parameter;
    for (offset = 0.0f; offset < range; offset += 10.0f) {
        parameter = func_0022E058(path, center - offset);
        func_0022E330(path, &backward, 0, parameter);
        if (func_001ED170(context, backward, flags)) {
            if (output)
                *output = parameter;
            return 1;
        }
        parameter = func_0022E058(path, center + offset);
        func_0022E330(path, &forward, 0, parameter);
        if (func_001ED170(context, forward, flags)) {
            if (output)
                *output = parameter;
            return 1;
        }
    }
    return 0;
}
