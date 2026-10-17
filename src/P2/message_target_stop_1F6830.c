// SLY3_CFLAGS: -Os -G0
struct StopMethod { short adjustment, word2; void *function; };
struct StopTable { unsigned char prefix[0x280]; struct StopMethod stop; };
struct StopMessage { int sender; int word4; int kind; };
struct StopSelf {
    unsigned char prefix0[0xC];
    struct StopTable *methods;
    unsigned char gap10[0x140 - 0x10];
    int owner;
    unsigned char gap144[0x198 - 0x144];
    void *resource;
};
void func_0013BEC0(struct StopSelf *self, int id, struct StopMessage *message);
void *func_001FE728(void *receiver, int flags);
void func_001F6830(struct StopSelf *self, int id, struct StopMessage *message)
{
    func_0013BEC0(self, id, message);
    if (id == 0xB) {
        if (message->sender == self->owner) {
            if (message->kind == 0x9D) {
                struct StopMethod *method;
                if (self->resource)
                    func_001FE728(self->resource, 1);
                method = &self->methods->stop;
                ((void (*)(void *, int))method->function)((char *)self + method->adjustment, -1);
            }
        }
    }
}
