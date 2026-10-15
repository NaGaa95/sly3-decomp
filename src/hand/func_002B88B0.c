// Construct the inherited receiver and four embedded receivers, install both original interface tables and return the receiver.
// Complete original body, actual inputs and every initialized section are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Receiver {
    char prefix[0xC];
    const void *primary;
    char middle[0x304];
    const void *secondary;
};
extern const char D_00353CC0[];
extern const char D_00353D00[];
void *func_002B5AA8(void *receiver);
void *func_002B8898(void *receiver);
void *func_002B8980(void *receiver);
void *func_002B8990(void *receiver);
void *func_002B8948(void *receiver);
struct Receiver *func_002B88B0(struct Receiver *p) {
    func_002B5AA8(p);
    func_002B8898((char *)p + 0x2F0);
    p->secondary = D_00353CC0;
    p->primary = D_00353D00;
    func_002B8980((char *)p + 0x320);
    func_002B8990((char *)p + 0xE40);
    func_002B8948((char *)p + 0x140C);
    return p;
}
