// SLY3_CFLAGS: -Os -G0
typedef struct ContextVector3 { float x, y, z; } ContextVector3;
typedef struct ContextPrefix {
    void *owner;
    int state4;
    char reserved8[0xC];
    float value14;
    float value18;
    float value1C;
    float value20;
    float value24;
    float value28;
    int reserved2C;
    ContextVector3 value30;
    char reserved3C[0xD0 - 0x3C];
    ContextVector3 valueD0;
    int reservedDC;
    ContextVector3 valueE0;
} ContextPrefix;

static inline void SetVector(ContextVector3 *vector, float x, float y, float z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void func_00271E38(ContextPrefix *context, void *owner)
{
    context->owner = owner;
    context->state4 = -1;
    context->value14 = 1.0f;
    context->value18 = 1.0f;
    context->value1C = 500.0f;
    context->value20 = 1500.0f;
    context->value24 = 1.5f;
    context->value28 = 1000.0f;
    SetVector(&context->value30, 0.0f, 0.0f, 25.0f);
    SetVector(&context->valueD0, 400.0f, 0.0f, 0.0f);
    SetVector(&context->valueE0, 42.0f, -73.0f, -50.0f);
}
