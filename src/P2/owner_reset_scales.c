// SLY3_CFLAGS: -Os -G0
struct Link {
    unsigned char prefix[0xDC];
    void *target;
};
struct Owner {
    unsigned char prefix[0xD8];
    struct Link *link;
    unsigned char gap[0x104 - 0xDC];
    float scale;
};
void func_001FCAC8(void *);
void func_00240DB0(void *);
void func_00241460(void *, float);
void func_0023C750(void *, void *);
void func_00242228(void *);
void func_001FCB20(struct Owner *owner)
{
    void *target;
    func_001FCAC8(owner);
    func_00240DB0(owner);
    owner->scale = 1.0f;
    func_00241460(owner, 0.0f);
    target = owner->link ? owner->link->target : 0;
    if (target)
        func_0023C750(owner, 0);
    func_00242228(owner);
}
