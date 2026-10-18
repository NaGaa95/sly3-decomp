// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct VirtualEntry { short delta; short reserved; void (*call)(void *); };
struct Node { unsigned int flags; };
struct Activation {
    unsigned char prefix[0xC];
    VirtualEntry *vtable;
    unsigned char gap10[0x2C - 0x10];
    Node *first;
    unsigned char gap30[4];
    Node *current;
    unsigned char gap38[0x88 - 0x38];
    float threshold;
};
typedef char ActivationPointerIs4[(sizeof(void *) == 4) ? 1 : -1];
typedef char VirtualEntryIs8[(sizeof(VirtualEntry) == 8) ? 1 : -1];
extern "C" {
extern const float D_00326434;
void func_00226D00(Activation *activation);
int func_0022BB50(Activation *activation);
void func_00226700(Activation *activation);
int func_00229438(Activation *activation, Node *node);
int func_00226578(Activation *activation);
void func_0022B930(Activation *activation);
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
    if (!activation->current && activation->threshold == D_00326434) {
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
