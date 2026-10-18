// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ColorBytes {
    unsigned char r, g, b, a;
};

struct Color {
    unsigned char r, g, b, a;
    Color(const Color &color) {
        *(ColorBytes *)this = *(const ColorBytes *)&color;
    }
} __attribute__((aligned(16)));

struct Manager {
    char pad[0x74];
    char *records;
};

struct Source {
    int unused;
    int kind;
    Manager *manager;
    int id;
    int index;
};

struct Event {
    char pad[0x30];
    Source *source;
    char pad34[0x58 - 0x34];
    int selection;
};

struct VirtualEntry {
    short delta, unused;
    void (*call)(void *);
};

struct Target {
    char pad[0xC];
    VirtualEntry *vtable;
};

extern "C" int func_00267270(void *);
extern "C" void func_00267028(void *, int, int, void *, Color, Color);
extern "C" Target *func_001E8A38(int);

extern "C" void func_00264478(Source *source, Event *event, void *data,
                                Color first, Color second)
{
    event->source = source;
    switch (source->kind) {
    case 4:
        event->selection = func_00267270(
            source->manager->records + source->index * 0x30);
        func_00267028(source->manager->records + source->index * 0x30,
                     0x37B, event->selection, data, first, second);
        break;
    case 6:
        if (source->id != -1) {
            Target *target = func_001E8A38(source->id);
            if (target)
                target->vtable[56].call(
                    (char *)target + target->vtable[56].delta);
        }
        break;
    }
}
