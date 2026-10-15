// When the receiver flag changes, retain or release the actual attached speaker according to its new value.
// Complete original input, boundary, relocation and whole initialized-section evidence are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Receiver {
    char prefix[0x174];
    int enabled;
};
struct Context {
    char prefix[0x1108];
    void *speaker;
};
extern struct Context *D_00370AC0;
void func_00173448(void *speaker);
void func_00173498(void *speaker);
void func_0022B238(struct Receiver *p, int enabled) {
    if (enabled != p->enabled) {
        void *speaker;
        p->enabled = enabled;
        speaker = D_00370AC0->speaker;
        if (speaker) {
            if (enabled) func_00173448(speaker);
            else func_00173498(speaker);
        }
    }
}
