// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct LightOwner { unsigned char opaque00[0x70]; unsigned char light[0x48]; int pending; };
extern Quad D_00479350;
void *func_00211110(void *list);
void func_00211170(void *list, void *light);
void func_0018E800(void *light, Quad color, void *matrix, float scale, float intensity, void *payload);
void func_001DC770(void *receiver)
{
    struct LightOwner *owner = (struct LightOwner *)receiver;
    if (owner->pending) {
        unsigned char list[0x410];
        func_00211110(list);
        func_00211170(list, owner->light);
    } else {
        func_0018E800(owner->light, D_00479350, 0, 1.0f, 1.0f, 0);
    }
}
