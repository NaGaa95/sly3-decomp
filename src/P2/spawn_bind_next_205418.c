// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VectorWord;
struct BindMethod { short adjustment, word2; void *function; };
struct BindTable { unsigned char prefix[0x120]; struct BindMethod query; };
struct BindReceiver { unsigned char prefix0[0xC]; struct BindTable *methods; };
struct BindSlot { unsigned char prefix0[0x40]; qword position; unsigned char gap50[0x50 - 0x50]; };
struct BindEntry { unsigned char prefix0[0x40]; qword position; int word50; };
struct BindSelf {
    unsigned char prefix0[0x3A4];
    void *resource;
    struct BindEntry *entry;
    int count;
    struct BindReceiver *receivers[4];
    int cursor;
    int limit;
    void *releases[1];
    unsigned char gap3CC[0x3D8 - 0x3CC];
    float rate;
    float offset;
    unsigned char gap3E0[4];
    float next;
};
void *func_001FBE30(void *resource, int flag);
void func_001C8FB0(void *object, void *receiver);
qword func_001C9428(void *source, void *destination, qword point);
int func_00205590(void *self, qword position, void *entry);
void func_00212770(void *entry, void *object);
int func_0013B500(void *object, int kind);
void func_0014D1F0(void *object, void *source);
void *func_001FE728(void *receiver, int flags);
extern float D_0036BB98;
void func_00205418(struct BindSelf *self)
{
    struct BindReceiver *receiver;
    void *object;
    if (self->resource && self->entry && self->count) {
        receiver = self->receivers[self->cursor];
        if (receiver) {
            object = func_001FBE30(self->resource, 0);
            if (object) {
                struct BindMethod *method;
                func_001C8FB0(object, receiver);
                self->entry->word50 = 0;
                method = &receiver->methods->query;
                if (!func_00205590(self, *(qword *)((char *)((void *(*)(void *))method->function)((char *)receiver + method->adjustment) + 0x30), (char *)self->entry + 0x40)) {
                    VectorWord offset;
                    struct BindEntry *target = self->entry;
                    offset.f[0] = self->offset;
                    offset.f[1] = 0.0f;
                    offset.f[2] = 0.0f;
                    target->position = func_001C9428(receiver, 0, offset.q);
                }
                func_00212770(self->entry, object);
                if (func_0013B500(object, 0x59))
                    func_0014D1F0(object, self);
                if (self->cursor < self->limit)
                    func_001FE728(self->releases[self->cursor], 1);
                self->cursor = (self->cursor + 1) % self->count;
            }
        }
    }
    self->next = D_0036BB98 + 1.0f / self->rate;
}
