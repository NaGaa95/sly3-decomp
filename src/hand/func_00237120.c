// Store the current engine clock and report whether this receiver's timestamp changed.
// Complete original inputs, concrete virtual bindings and whole code/data are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Receiver {
    char prefix[0x10];
    float timestamp;
};
extern float D_0036BB98;
int func_00237120(struct Receiver *p) {
    if (p->timestamp != D_0036BB98) {
        p->timestamp = D_0036BB98;
        return 1;
    }
    return 0;
}
