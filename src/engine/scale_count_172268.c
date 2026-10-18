// SLY3_CFLAGS: -Os -G0
struct ScaleRow { unsigned char prefix[0x20]; float low; float high; };
struct ScaleSelf { unsigned char prefix[0x14]; struct ScaleRow *row; };
int func_0013B500(void *object, int identifier);
int func_001F4350(void *object, int value);
float func_00171C98(void *self);
int func_00172268(struct ScaleSelf *self, int limit, void *object)
{
    if(func_0013B500(object, 0x31) && func_001F4350(object, -1)) {
        float factor = func_00171C98(self);
        int value = (int)(((1.0f - factor) * self->row->low + factor * self->row->high) * (float)limit);
        if(limit > 0) {
            if(value <= 1) value = 1;
        }
        return value;
    }
    return limit;
}
