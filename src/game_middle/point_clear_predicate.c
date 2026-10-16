// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int QueryPoint __attribute__((mode(TI)));
void *func_001EB4C8(void *, QueryPoint, int);
int func_001EDFE0(void *, int cache_address, QueryPoint, QueryPoint, int, void **);
int func_001E6BF0(void *, QueryPoint);

int func_001ED1F0(void *context, QueryPoint point, int flags)
{
    void *objects[0x80];
    int count, index;
    if (!func_001EB4C8((char *)context + 0xD0, point, flags))
        return 0;
    count = func_001EDFE0(context, 0, point, point, 0x80, objects);
    for (index = 0; index < count; index++) {
        if (func_001E6BF0(objects[index], point))
            return 0;
    }
    return 1;
}
