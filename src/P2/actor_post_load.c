// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct ACTOR_FIELD { int flags, identifier, offset; };
struct ActorPostLoadView {
    char prefix[0x48];
    void *first_channel, *second_channel;
};
struct ActorPostLoadResource {
    char prefix[0xE0];
    int enabled;
};
extern const struct ACTOR_FIELD D_00346FC0[];
void func_0023C0B8(void *receiver, void *stream);
void *func_00241268(void *receiver);
void func_0028F068(void *receiver, void *channel, int mode);
void func_001C8970(void *receiver, int count, const struct ACTOR_FIELD *fields, void *parent);

void func_001F6668(struct S *receiver, void *stream) {
    struct ActorPostLoadView *p = (struct ActorPostLoadView *)receiver;
    struct ActorPostLoadResource *resource;
    func_0023C0B8(receiver, stream);
    resource = (struct ActorPostLoadResource *)func_00241268(receiver);
    resource->enabled = 1;
    func_0028F068(receiver, p->first_channel, 0x16);
    func_0028F068(receiver, p->second_channel, 0);
    func_001C8970(receiver, 1, D_00346FC0, 0);
}

typedef char ActorPostLoadWidths[(sizeof(void *) == 4 && sizeof(int) == 4 && sizeof(struct ACTOR_FIELD) == 12 && sizeof(struct ActorPostLoadView) == 0x50 && sizeof(struct ActorPostLoadResource) == 0xE4) ? 1 : -1];
