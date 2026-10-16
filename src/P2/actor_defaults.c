// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ActorDefaultList { void *first, *last; int link_offset; };
struct ActorDefaultView {
    char prefix[0x3C];
    int tagged_flags;
    char reserved40[0x130 - 0x40];
    int selection;
    void *input;
    char reserved138[0x158 - 0x138];
    struct ActorDefaultList children;
    char reserved164[0x188 - 0x164];
    int marker;
};
extern char D_0036E6D0[];
void func_0023AE08(void *receiver);
void func_0011AF38(void *list, int link_offset);

void func_001F3B50(void *receiver) {
    struct ActorDefaultView *p = (struct ActorDefaultView *)receiver;
    int absent;
    int flags;

    func_0023AE08(receiver);
    absent = -1;
    p->selection = absent;
    p->input = D_0036E6D0;
    func_0011AF38(&p->children, 0x64);
    p->marker = absent;
    flags = p->tagged_flags;
    if ((flags ^ 1) & 1)
        *(int *)flags |= 2;
    else
        p->tagged_flags = flags | 2;
}

typedef char ActorDefaultWidths[(sizeof(void *) == 4 && sizeof(int) == 4 && sizeof(struct ActorDefaultList) == 12 && sizeof(struct ActorDefaultView) == 0x18C) ? 1 : -1];
