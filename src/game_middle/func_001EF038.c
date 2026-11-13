// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
// Allocates a record from the pool at D_0047A400 and links it into its list. With an owner that accepts the
// position/direction (func_001EC6E8) the record is attached to it; otherwise it becomes a free record (mode 2) whose
// direction is position + axis * 5. The axis is passed by address so it is loaded inside the helper body.
typedef int RecordPacked __attribute__((mode(TI)));
typedef union { RecordPacked raw; float scalar; } RecordScalarCarrier;
struct RecordOwner { unsigned char prefix[0x104]; int word104; };
struct Record {
    unsigned char prefix00[4];
    float x04;
    float x08;
    unsigned char gap0C[4];
    RecordPacked q10;
    RecordPacked q20;
    int mode;
    unsigned char gap34[0x40 - 0x34];
    RecordPacked position;
    RecordPacked direction;
    unsigned char gap60[0x140 - 0x60];
    RecordPacked q140;
    unsigned char gap150[0x240 - 0x150];
    float f240;
    float f244;
    unsigned char gap248[0x280 - 0x248];
    struct RecordOwner *owner;
    int index;
};
extern char D_0047A400[];
extern RecordPacked D_00317530;
void *func_0011E118(void *pool);
void func_0011AF60(void *list, void *object);
int func_001EC6E8(struct RecordOwner *owner, RecordPacked position, RecordPacked direction, struct Record *record);
void func_001EF608(struct Record *record);

static inline RecordPacked record_offset(RecordPacked position, const RecordPacked *axis, float scale)
{
    RecordScalarCarrier carrier;
    RecordPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
            : "=j"(result) : "j"(position), "j"(*axis), "j"(carrier.raw));
    return result;
}

struct Record *func_001EF038(RecordPacked position, RecordPacked direction, struct RecordOwner *owner)
{
    struct Record *record = func_0011E118(D_0047A400);
    func_0011AF60(D_0047A400 + 0x18, record);
    if (!owner) {
        record->mode = 2;
        record->position = position;
        record->direction = direction;
        func_001EF608(record);
        record->owner = 0;
        record->index = -1;
    } else if (func_001EC6E8(owner, position, direction, record)) {
        func_001EC6E8(owner, position, direction, record);
        record->owner = owner;
        record->index = owner->word104;
    } else {
        record->mode = 2;
        record->position = position;
        record->direction = record_offset(position, &D_00317530, 5.0f);
        func_001EF608(record);
        record->owner = 0;
        record->index = -1;
    }
    record->x04 = record->f240;
    record->x08 = record->f244;
    record->q10 = record->position;
    record->q20 = record->q140;
    return record;
}
