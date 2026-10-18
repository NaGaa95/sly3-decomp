// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Record;
struct Control { int count; Record *records; unsigned char gap8[0x10]; };
struct Group { unsigned short count; unsigned short controlCount; void *events; Control *controls; unsigned char gapC[0x24]; };
struct Screen { unsigned char prefix[0x74]; Group *groups; };
struct Object { unsigned char gap0[4]; int kind; unsigned char gap8[8]; int group; };
struct Record {
    unsigned char prefix[0x10];
    unsigned char tail10[0x20];
    Object *object;
    unsigned char gap34[0x58 - 0x34];
    int index;
    unsigned char gap5C[0x64 - 0x5C];
    int word64;
    unsigned char pair68[8];
};
struct RGBA { unsigned int u; RGBA(unsigned int x) { u = x; } } __attribute__((aligned(16)));
extern "C" {
void func_00267888(void *group, int index);
void func_0011AD68(void *pair);
int func_00267270(void *group);
void func_00267110(float f, void *group, int l, int index, void *q, const RGBA &c0, const RGBA &c1);
}
extern "C" int func_00262D28(Screen *p, int j, int l, int count, Record *records)
{
    int i;
    if (!records) {
        Control *first = p->groups->controls;
        count = first->count;
        records = first->records;
    }
    for (i = 0; i < count; i++) {
        Record *record = &records[i];
        Object *object = record->object;
        if (object && object->kind == 4) {
            int index = record->index;
            if (object->group == j) {
                func_00267888(&p->groups[j], index);
                func_0011AD68(record->pair68);
                record->index = func_00267270(&p->groups[j]);
                RGBA c0(0x7F7F7F7F), c1(0xFFFFFFFF);
                func_00267110(0.0f, &p->groups[j], l, record->index, record->tail10, c0, c1);
                return 1;
            }
            {
                Control *controls = p->groups[object->group].controls;
                Control *control = (Control *)(index * sizeof(Control) + (int)controls);
                if (func_00262D28(p, j, l, control->count, control->records))
                    return 1;
            }
        }
    }
    return 0;
}
