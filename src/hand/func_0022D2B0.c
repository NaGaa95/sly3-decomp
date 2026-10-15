// Reset the attached actor property selected by its actual integer key.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Actor;
struct Reference {
    struct Actor *actor;
};
struct Context {
    char prefix[0x14];
    struct Reference *reference;
};
struct Receiver {
    char prefix[0x15E0];
    struct Context *context;
};
int func_0013B500(void *receiver, int type);
void *func_002387A8(void *list, int property);
void func_001F5CF0(void *receiver);
void func_0022D2B0(struct Receiver *p) {
    if (p->context && func_0013B500(p->context->reference->actor, 0x32)) {
        void *property = func_002387A8((char *)p->context->reference->actor + 0x29C, 0xE8);
        if (property) func_001F5CF0(property);
    }
}
