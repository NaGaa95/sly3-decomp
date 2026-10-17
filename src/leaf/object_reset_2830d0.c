// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Object {
    unsigned char prefix[0x40];
    int word40, word44, word48;
    unsigned char gap4C[0xC];
    int word58, word5C, word60, word64;
    unsigned char gap68[4];
    int word6C;
    unsigned char gap70[0x10];
    float scale80;
    unsigned char gap84[4];
    int word88, word8C;
    float scale90;
};
struct Globals { unsigned char prefix[0x4034]; int counter; };
extern struct Globals D_00475480;
void func_001C7340(void *receiver);
void func_002830D0(struct Object *o)
{
    func_001C7340(o);
    o->word64=2;
    o->word88=1;
    o->scale80=1.0f;
    o->scale90=1.0f;
    o->word8C=-1;
    o->word48=-1;
    o->word58=-1;
    o->word5C=-1;
    o->word60=-1;
    o->word6C=-1;
    o->word40=-1;
    o->word44=-1;
    D_00475480.counter++;
}
