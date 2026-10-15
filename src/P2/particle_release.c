// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Property;
struct S;
typedef struct DL {
    void *pvFirst, *pvLast;
    int ibDle;
} DL;
struct ReleaseOwnerView {
    unsigned char prefix[0x6C];
    DL properties;
};
struct ReleasePropertyView {
    struct ReleaseOwnerView *owner;
    unsigned char prefix[0xC - 4];
    void *sound;
};
void func_00244CA8(struct S *, float value);
void func_002BE970(void **reference, void *value);
void func_0011B028(DL *list, void *object);

void func_001FF098(struct Property *property)
{
    struct ReleasePropertyView *p = (struct ReleasePropertyView *)property;
    void **sound = &p->sound;
    if (sound && *sound) {
        func_00244CA8((struct S *)*sound, 0.0f);
        func_002BE970(sound, 0);
    }
    func_0011B028(&p->owner->properties, property);
}
