// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Manager {
    char pad[0x74];
    char *records;
};

struct EventSource {
    int unused;
    int kind;
    struct Manager *manager;
    int unusedC;
    int index;
};

struct Event {
    char pad[0x58];
    int selection;
};

void func_00267818(void *, int);
void func_0011ADA8(void *, struct Event *);

void func_002647A0(struct EventSource *source, struct Event *event)
{
    switch (source->kind) {
    case 4:
        func_00267818(source->manager->records + source->index * 0x30,
                     event->selection);
        break;
    case 1:
    case 3:
    case 6:
    case 7:
        func_0011ADA8((char *)source->manager + 0xF4, event);
        break;
    case 2:
    case 5:
        break;
    }
}
