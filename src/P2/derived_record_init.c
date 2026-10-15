// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Complete USA constructor 0x001FDE70; original three physical inputs.
struct MSG { int cb; int nKind; };
struct VECTOR3_VIEW { float x, y, z; };
struct SECOND_RECORD_VIEW {
    unsigned char prefix[0x20];
    struct VECTOR3_VIEW vector;
};
struct DERIVED_RECORD_VIEW {
    unsigned char prefix[0x14];
    struct SECOND_RECORD_VIEW *second;
    void *vtable;
    void *extra;
};
static inline void SetVector(struct VECTOR3_VIEW *vector, float x, float y, float z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}
extern unsigned char D_00361418[], D_00347F38[];
void *func_001FCCE8(void *, void *, int);
void *func_001D24D0(struct MSG *, void *);

void *func_001FDE70(void *receiver, void *owner, int value)
{
    struct MSG request;
    struct DERIVED_RECORD_VIEW *object = receiver;
    func_001FCCE8(receiver, owner, value);
    object->vtable = D_00361418;
    request.nKind = 16;
    request.cb = 36;
    object->extra = func_001D24D0(&request, D_00347F38);
    SetVector(&object->second->vector, 1.0f, 0.0f, 0.0f);
    return receiver;
}
