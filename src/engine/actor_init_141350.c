// SLY3_CFLAGS: -Os -G0
struct Shuffled;
struct SlotObject { unsigned char prefix[0x10]; void *peer; };
struct InitSlot { struct SlotObject *object; void *extra; };
struct InitSelf {
    unsigned char prefix[0x48]; void *boneA; void *boneB;
    unsigned char gap50[0x198 - 0x50]; int created;
    unsigned char gap19C[0x360 - 0x19C]; struct InitSlot slots[4];
    unsigned char gap380[0x39C - 0x380]; int serial;
    unsigned char gap3A0[0x434 - 0x3A0]; struct Shuffled *shuffle;
    unsigned char gap438[0x454 - 0x438]; void *back;
    unsigned char gap458[0x468 - 0x458]; float low; float high; unsigned char gap470[4]; float half;
    unsigned char gap478[0x4A4 - 0x478]; void *resource; void *reference;
};
struct InitGame { unsigned char prefix[0x4E2C]; float scale; unsigned char gap4E30[4]; int serial; };
extern struct InitGame D_00475480;
extern char D_0036B118[];
void func_001F3BF8(void *self);
void func_00146F18(void *self);
void func_001F4670(void *self, int value);
void *func_001D27F0(unsigned int bytes);
struct Shuffled *func_002BC1C8(void *storage, int count, const int *identifiers, void *heap);
void *func_001507E0(void *object, void *peer);
void *func_002399C8(void *resource, void *receiver, int identifier, int mode);
void func_0028F068(void *self, void *bone, int mode);
void func_00141350(struct InitSelf *self)
{
    struct SlotObject *object;
    unsigned int i;
    func_001F3BF8(self);
    func_00146F18(self);
    if(!self->created) {
        func_001F4670(self, 1);
        {
            int ids[7] = {54, 55, 56, 57, 58, 59, 60};
            self->shuffle = func_002BC1C8(func_001D27F0(20), 7, ids, D_0036B118);
        }
    }
    object = self->slots[0].object;
    if(object) {
        for(i = 1; i < 4; i++) self->slots[i].object = func_001507E0(object, object->peer);
    }
    self->back = self;
    self->half = 0.5f;
    self->low = D_00475480.scale * 0.45f;
    self->high = D_00475480.scale * 0.55f;
    if(self->resource) self->reference = func_002399C8(self->resource, self, -1, 1);
    func_0028F068(self, self->boneA, 2);
    func_0028F068(self, self->boneB, 2);
    self->serial = D_00475480.serial++;
}
