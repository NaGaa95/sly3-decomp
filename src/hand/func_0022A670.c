// Evaluate an enabled scalar parameter using its packed kind byte.
// Kind and partial-view names are provisional; IDs and consumed offsets are
// original. A byte-sized zero-based kind index retains the wrapped range check.
// SLY3_CFLAGS: -Os -G0
struct PARAMETER_CONTEXT;
struct QUERY_ARGUMENTS { int objectId; int secondaryId; int fieldId; };
struct RESOURCE_ARGUMENTS { char unknown[0x1c]; int id; };
union PARAMETER_VALUE {
    float value;
    float *storedValue;
    struct QUERY_ARGUMENTS *query;
    struct RESOURCE_ARGUMENTS *resource;
};
enum __attribute__((packed)) PARAMETER_KIND {
    PARAMETER_POLYNOMIAL=0x16, PARAMETER_QUERY=0x19,
    PARAMETER_STORED=0x2f, PARAMETER_ALTERNATE_A=0x38,
    PARAMETER_ALTERNATE_B=0x39, PARAMETER_HALF=0x3f,
    PARAMETER_DIRECT=0x40, PARAMETER_RESOURCE=0x52,
    PARAMETER_ALTERNATE_C=0x60
};
union PARAMETER_TAG {
    unsigned int word;
    struct { enum PARAMETER_KIND kind; unsigned char flags; unsigned short reserved; } fields;
};
struct SCALAR_PARAMETER {
    union PARAMETER_TAG tag;
    int unknown4;
    union PARAMETER_VALUE payload;
    float alternateValue;
};
struct SAMPLE_OBJECT {
    char unknown[0x64];
    float numerator;
    float scale;
    int unknown6c;
    float coefficients[3];
    int unknown7c;
    float minimum;
    float maximum;
};
extern char D_0036BD20[];
extern char D_00474FF0[];
extern float D_00344838;
void *func_00226770(struct PARAMETER_CONTEXT *context, int id);
float func_00171C98(void *timer);
void *func_0023FB68(void *object, int id);
float func_0023A850(void *record, int fieldId);
float func_00246E40(void *catalog, int id);
static __inline__ float ClampSample(float value, float minimum, float maximum)
{
    if (value < minimum) return minimum;
    if (value > maximum) return maximum;
    return value;
}
typedef char parameter_kind_is_1[sizeof(enum PARAMETER_KIND) == 1 ? 1 : -1];
typedef char parameter_tag_is_4[sizeof(union PARAMETER_TAG) == 4 ? 1 : -1];
typedef char sample_consumed_prefix_is_136[sizeof(struct SAMPLE_OBJECT) == 0x88 ? 1 : -1];
typedef char query_arguments_is_12[sizeof(struct QUERY_ARGUMENTS) == 12 ? 1 : -1];
typedef char resource_arguments_prefix_is_32[sizeof(struct RESOURCE_ARGUMENTS) == 32 ? 1 : -1];
typedef char scalar_parameter_is_16[sizeof(struct SCALAR_PARAMETER) == 16 ? 1 : -1];

float func_0022A670(struct PARAMETER_CONTEXT *context, struct SCALAR_PARAMETER *parameter)
{
    float value = 0.0f;
    unsigned char kindIndex;
    if (!(parameter->tag.word & 0x100)) return value;
    kindIndex = parameter->tag.fields.kind - PARAMETER_POLYNOMIAL;
    switch (kindIndex) {
    case 0x16 - PARAMETER_POLYNOMIAL: {
        struct SAMPLE_OBJECT *object = func_00226770(context, parameter->payload.query->objectId);
        if (object) {
            float time = func_00171C98(D_0036BD20);
            float *coefficients = object->coefficients;
            float sample = coefficients[0] + time * (coefficients[1] + time * coefficients[2]);
            sample = ClampSample(sample, object->minimum, object->maximum);
            value = object->numerator / (object->scale * sample);
        }
        break;
    }
    case 0x19 - PARAMETER_POLYNOMIAL:
        if (parameter->payload.query->fieldId != -1) {
            void *object = func_00226770(context, parameter->payload.query->objectId);
            if (object) {
                void *record = func_0023FB68(object, parameter->payload.query->secondaryId);
                if (record) value = func_0023A850(record, parameter->payload.query->fieldId);
            }
        }
        break;
    case 0x2f - PARAMETER_POLYNOMIAL:
        value = *parameter->payload.storedValue;
        break;
    case 0x3f - PARAMETER_POLYNOMIAL:
        value = D_00344838;
        break;
    case 0x40 - PARAMETER_POLYNOMIAL:
        value = parameter->payload.value;
        break;
    case 0x52 - PARAMETER_POLYNOMIAL:
        value = func_00246E40(D_00474FF0, parameter->payload.resource->id);
        break;
    case 0x38 - PARAMETER_POLYNOMIAL:
    case 0x39 - PARAMETER_POLYNOMIAL:
    case 0x60 - PARAMETER_POLYNOMIAL:
        value = parameter->alternateValue;
        break;
    }
    return value;
}
