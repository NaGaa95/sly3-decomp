// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// func_00226578, func_002265E0 and func_00226950 share one translation unit: the original .rodata starts at 0x326430 with the
// FLT_MAX literals of the first two, followed by the level-id table and the jump table of func_00226950.
extern "C" {
#include "eval_dispatch_api.h"
}
struct VirtualEntry { short delta; short reserved; void (*call)(void *); };
struct Node { unsigned int flags; };
struct Activation {
    unsigned char prefix[0xC];
    VirtualEntry *vtable;
    unsigned char gap10[4];
    void *object;
    unsigned char gap18[0x2C - 0x18];
    Node *first;
    unsigned char gap30[4];
    Node *current;
    unsigned char gap38[0x88 - 0x38];
    float threshold;
};
typedef char ActivationPointerIs4[(sizeof(void *) == 4) ? 1 : -1];
typedef char VirtualEntryIs8[(sizeof(VirtualEntry) == 8) ? 1 : -1];
extern "C" {
float func_00226458(void *receiver);
void func_00226D00(Activation *activation);
int func_0022BB50(Activation *activation);
void func_00226700(Activation *activation);
int func_00229438(Activation *activation, Node *node);
void func_0022B930(Activation *activation);
}
// func_00226578: compare the actual selected object clock against the receiver threshold, preserving sentinel behavior.
extern "C" int func_00226578(Activation *p)
{
    int result = 0;
    if (p->threshold != 3.4028235e38f) {
        if (func_00226458(p->object) < p->threshold)
            result = 1;
    }
    return result;
}
class ScopedBracket {
    Activation *activation;
public:
    ScopedBracket(Activation *a) : activation(a)
    {
        VirtualEntry *entry = &activation->vtable[1];
        entry->call((char *)activation + entry->delta);
    }
    ~ScopedBracket()
    {
        VirtualEntry *entry = &activation->vtable[2];
        entry->call((char *)activation + entry->delta);
    }
};
extern "C" void func_002265E0(Activation *activation)
{
    ScopedBracket bracket(activation);
    Node *node;
    if (!activation->current && activation->threshold == 3.4028235e38f) {
        activation->current = activation->first;
        func_00226D00(activation);
        if (func_0022BB50(activation))
            return;
    }
    while ((node = activation->current) != 0 && (!(node->flags & 0x100) || func_00229438(activation, node))) {
        func_00226700(activation);
        func_00226D00(activation);
        if (func_0022BB50(activation))
            return;
    }
    func_00226700(activation);
    if (!activation->current && !func_00226578(activation))
        func_0022B930(activation);
}

// func_00226950: evaluate the condition kind (0x75E-0x767) against the object or argument; unknown kinds are forwarded to the handler method and its result reference.
class ResultReference {
public:
    CRef value;
    ResultReference() { value.tag = -1; }
    void Drop() __asm__("func_0012BC20");
    ~ResultReference() { Drop(); }
};
struct Entry { short delta, reserved; void (*call)(void *, int, int, int, int **, CRef *); };
struct Handler { unsigned char opaque00[0xC]; Entry *table; };
struct Self { unsigned char opaque00[0x14]; Handler *handler; };
struct Record {
    unsigned char opaque00[0x54];
    int state;
    unsigned char opaque58[0xFC - 0x58];
    int mode;
};
extern "C" {
extern unsigned char D_00475480[];
extern unsigned char D_00474FF0[];
void *func_0017E1B8(void *game, int flags, int key, void *owner);
int func_00226270(Handler *handler, int arg);
int func_0025E7A8(void);
int func_00248858(void *context, int item);
}
extern "C" int func_00226950(Self *self, int id, int arg)
{
    switch (id) {
    case 0x75E:
        return 1;
    case 0x760:
    case 0x761:
    case 0x762: {
        Record *record = (Record *)func_0017E1B8(D_00475480, 5, arg, 0);
        switch (id) {
        case 0x760: return record->state == 1;
        case 0x761: return record->mode == 0;
        case 0x762: return record->mode == 1;
        }
        return 0;
    }
    case 0x75F:
        return 0;
    case 0x763:
        return func_00226270(self->handler, arg);
    case 0x764:
        return func_00226270(self->handler, arg) == 0;
    case 0x765: {
        static const int levelIds[5] = { 0x768, 0x769, 0x76A, 0x76B, 0x76C };
        return levelIds[func_0025E7A8()] == arg;
    }
    case 0x767:
        return func_00248858(D_00474FF0, -1);
    case 0x766:
        return func_00248858(D_00474FF0, -1) == 0;
    }
    {
        ResultReference result;
        int *pointer = &id;
        self->handler->table[3].call((char *)self->handler + self->handler->table[3].delta, 4, 0, 1, &pointer, &result.value);
        return result.value.payload.integer;
    }
}
