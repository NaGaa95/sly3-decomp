// Report whether the descriptor for the id exists, its prerequisite id passes, and the current level meets its requirement.
// SLY3_CFLAGS: -Os -G0
struct Descriptor {
    unsigned char opaque00[0x14];
    int first;
    int second;
    unsigned char opaque1C[0x3C - 0x1C];
};
extern struct Descriptor D_00343098[];
extern unsigned char D_00475480[];
extern unsigned char D_00468D30[];
int func_0021F410(int id);
int func_0025E198(void *record);
int func_0025EBC0(void *table, int first, int second, int other);

int func_0021F350(int id)
{
    struct Descriptor *descriptor = &D_00343098[id];
    if (descriptor->first == -1) return 0;
    switch (id) {
    case 0x2A:
    case 0x2B:
    case 0x2D:
    case 0x2E:
    case 0x30:
    case 0x31:
        if (!func_0021F410(id - 1)) return 0;
        break;
    case 0x22:
        if (!func_0021F410(0x20)) return 0;
        break;
    }
    return func_0025EBC0(D_00475480, descriptor->first, descriptor->second, func_0025E198(D_00468D30));
}
