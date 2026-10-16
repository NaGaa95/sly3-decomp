// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct Property;
struct DL;
struct PropertyConstructView {
    void *owner, *definition;
    int unused8;
    void *sound;
    float started;
    int event_index;
    float accumulator, rate;
    int repeats;
    char reserved24[0x40 - 0x24];
    void *methods;
};
struct PropertyDefinitionPrefix { char prefix[8]; short repeats; };
extern unsigned char D_003615F8[];
void func_0011AF60(struct DL *list, void *object);
void func_001FF3E0(struct Property *property);

struct S *func_001FEEF8(struct S *receiver, void *owner, void *definition)
{
    struct PropertyConstructView *object = (struct PropertyConstructView *)receiver;
    object->owner = owner;
    object->definition = definition;
    object->methods = D_003615F8;
    object->sound = 0;
    object->repeats = ((struct PropertyDefinitionPrefix *)definition)->repeats;
    func_0011AF60((struct DL *)((char *)owner + 0x6C), receiver);
    object->event_index = -1;
    func_001FF3E0((struct Property *)receiver);
    return receiver;
}
