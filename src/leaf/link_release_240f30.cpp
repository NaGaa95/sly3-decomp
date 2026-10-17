// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef unsigned int Quad __attribute__((mode(TI)));
union ModeState {
    unsigned long value;
    struct {
        unsigned long low:32;
        unsigned char byte124:8;
        unsigned char byte125:8;
        unsigned long unknown126:8;
        unsigned int mode:2;
        unsigned long rest:6;
    } __attribute__((packed)) fields;
} __attribute__((packed,aligned(8)));
struct LinkEntry {
    unsigned char prefix[0x18];
    union {
        unsigned long word;
        struct { unsigned short identifier; unsigned short middle; unsigned int flags; } half;
    };
};
struct LinkEnd {
    LinkEntry *entry;
    unsigned char gap4[4];
    void *owner;
    void *word;
    Quad position;
    unsigned char gap20[0x10];
    Quad direction;
};
struct Link {
    LinkEnd ends[2];
    unsigned char gap80[0xAC - 0x80];
    Link *next;
};
struct LinkGroup { unsigned char prefix[0x6C]; Link *links; };
struct VirtualEntry { short delta, reserved; void *call; };
struct LinkObject {
    unsigned char prefix[0xC];
    VirtualEntry *vtable;
    unsigned char gap10[0xDC - 0x10];
    LinkGroup *group;
    unsigned char gapE0[0x120 - 0xE0];
    ModeState state;
};
extern "C" {
extern char D_00475480[];
extern void *D_0038AE90;
void func_00240CB0(void *receiver, void *entry, void *owner, int flags, int identifier, int active, Quad position, Quad direction, void *output);
void func_001CBAA0(char *pool, Link *links);
void func_00241150(LinkObject *object, int mode);
int func_0013B500(LinkObject *object, int event);
}
extern "C" void func_00240F30(LinkObject *self)
{
    if (self->group) {
        Link *list = self->group->links;
        self->group->links = 0;
        for (Link *link = list; link; link = link->next) {
            int side = link->ends[0].owner != self;
            LinkEnd *own = &link->ends[side];
            LinkEntry *entry = own->entry;
            if (entry->half.flags) {
                void **firstWord = &link->ends[0].word;
                func_00240CB0(self, entry, *(void **)((char *)firstWord + (1 - side) * 64), entry->half.flags, entry->half.identifier, ((int)(entry->word >> 21)) & 1, ((LinkEnd *)((char *)link + (1 - side) * 64))->position, own->direction, 0);
                if (!self->group)
                    break;
            }
        }
        func_001CBAA0(D_00475480, list);
    }
    if (self->group) {
        int mode = self->state.fields.mode;
        if (mode) {
            func_00241150(self, 0);
            if (mode == 3 && func_0013B500(self, 0x3A)) {
                VirtualEntry *entry = &self->vtable[36];
                char *matrix = ((char *(*)(void *))entry->call)((char *)self + entry->delta);
                Quad position = *(Quad *)(matrix + 0x30);
                entry = &self->vtable[38];
                Quad direction = ((Quad (*)(void *))entry->call)((char *)self + entry->delta);
                func_00240CB0(D_0038AE90, 0, self, 0x40000, 0x32, 0, position, direction, 0);
            } else {
                VirtualEntry *entry = &self->vtable[36];
                char *matrix = ((char *(*)(void *))entry->call)((char *)self + entry->delta);
                Quad position = *(Quad *)(matrix + 0x30);
                entry = &self->vtable[38];
                Quad direction = ((Quad (*)(void *))entry->call)((char *)self + entry->delta);
                func_00240CB0(self, 0, self, 0x20000, self->state.fields.byte125, 0, position, direction, 0);
            }
        }
    }
}
