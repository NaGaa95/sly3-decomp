// Run the inherited reset, restore unit weight and update the actual64-bit and tagged-word flags.
// Complete original input, boundary, relocation and whole initialized-section evidence are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int U64 __attribute__((mode(DI)));
struct Receiver {
    char prefix[0x3C];
    unsigned int tagged;
    char middle[0xE8];
    U64 flags;
    char end[0x70];
    float weight;
};
void func_002236E8(void *receiver);
void func_002238B0(struct Receiver *p) {
    unsigned int tagged;
    func_002236E8(p);
    p->weight = 1.0f;
    tagged = p->tagged;
    p->flags &= ~(U64)8;
    if ((tagged ^ 1) & 1) *(unsigned int *)tagged |= 8;
    else p->tagged = tagged | 8;
}
