// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct Object { unsigned char pad[0x40]; Quad transform[4]; unsigned char gap[0x24]; int value; } Object;
typedef struct Record {
    Object *object; unsigned char pad[0x14]; unsigned long flags;
    unsigned char gap[0x10]; Quad transform[4]; unsigned char gap2[0x48]; int value;
    unsigned char tail[0x14];
} Record;
typedef struct State { unsigned char pad[0xD0]; int count; Record *records; } State;
// Refresh cached transforms and metadata unless the record excludes updates.
void func_0023C878(State *state)
{
    int index;
    for (index = 0; index < state->count; index++) {
        Record *record = &state->records[index];
        if (!(record->flags & 0x80000)) {
            Object *object = record->object;
            record->transform[0] = object->transform[0];
            record->transform[1] = object->transform[1];
            record->transform[2] = object->transform[2];
            record->transform[3] = object->transform[3];
            record->value = object->value;
        }
    }
}
