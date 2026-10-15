// Initialize the original descriptor fields and explicitly enter state zero.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Descriptor {
    int kind, flags;
    unsigned short firstCount, secondCount;
    float first, second, third, fourth;
    int configuration;
};
struct Receiver {
    char prefix[0x50];
    float first, second, third, fourth;
    int configuration, state;
};
void func_00236FE0(void *receiver, const void *descriptor);
void func_002378C0(void *receiver, int state);
void func_00237850(struct Receiver *p, const struct Descriptor *descriptor) {
    func_00236FE0(p, descriptor);
    p->configuration = descriptor->configuration;
    p->first = descriptor->first;
    {
        float second = descriptor->second;
        float third = descriptor->third;
        p->second = second;
        p->third = third;
    }
    p->fourth = descriptor->fourth;
    p->state = -1;
    func_002378C0(p, 0);
}
