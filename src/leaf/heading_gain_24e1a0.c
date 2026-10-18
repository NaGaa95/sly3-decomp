// SLY3_CFLAGS: -Os -G0
struct HeadingGainMethod { short adjustment, reserved; float *(*query)(void *); };
struct HeadingGainView {
    unsigned char prefix[0xC];
    struct HeadingGainMethod *table;
    unsigned char toGain[0x190 - 0x10];
    float gain;
    unsigned char toMode[0x1B8 - 0x194];
    int mode;
    float heading;
    unsigned char toActive[0x218 - 0x1C0];
    int active;
    float updated;
};
extern float D_00327230[3], D_00341FF0[2], D_0036BB98;
void func_0023C660(void *);
void func_0024DFC8(void *, int);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
void func_0024E1A0(void *receiver)
{
    struct HeadingGainView *object = receiver;
    func_0023C660(receiver);
    func_0024DFC8(receiver, 0);
    switch (object->mode) {
    case 0: {
        struct HeadingGainMethod *method = object->table + 36;
        float *matrix = method->query((char *)object + method->adjustment);
        float difference = func_0011E3B8(object->heading -
            func_002A3EE8(matrix[1], matrix[0]));
        float gain;
        float low = D_00341FF0[0];
        float high = D_00341FF0[1];
        difference = __builtin_fabsf(difference);
        gain = D_00327230[0] + difference *
            (D_00327230[1] + difference * D_00327230[2]);
        if (gain < low)
            gain = low;
        else if (high < gain)
            gain = high;
        object->gain = gain;
        break;
    }
    case 1:
    case 2:
        object->gain = 1.0f;
        break;
    }
    if (object->active)
        object->updated = D_0036BB98;
}
