// SLY3_CFLAGS: -O2 -G0
typedef int FlagValue __attribute__((mode(DI)));
typedef struct ObjectState {
    unsigned char opaque0[16];
    int owner;
    int resource;
    unsigned char opaque1[23];
    unsigned char flags;
    unsigned char opaque2[20];
    int state;
} ObjectState;
extern unsigned char D_00475480[];
extern void func_0015ADA0(void *manager, int resource);

void func_00290078(ObjectState *object)
{
    if (object->state != -1) {
        int narrow;
        FlagValue flags = object->flags;
        // Preserve the observed flag conversion and its lifetime before the
        // state-clearing store. These constraints emit no instructions.
        asm("" : "+r"(flags));
        narrow = (int)flags;
        asm("" : "+r"(narrow) : : "memory");
        object->state = -1;
        if ((narrow & 1) && object->owner == 0)
            func_0015ADA0(D_00475480, object->resource);
    }
}
