// SLY3_CFLAGS: -Os -G0
struct RefNode { int id; int cref; struct RefNode *pnext; };
struct RefOwner { unsigned char prefix[0xE4]; struct RefNode *pfirst; };
extern char D_004798D0[];
void *func_0011E118(void *pool);
void func_0020C6C8(struct RefOwner *owner, int id)
{
    struct RefNode *node = (struct RefNode *)func_0011E118(D_004798D0);
    node->id = id;
    node->pnext = owner->pfirst;
    owner->pfirst = node;
}
struct RefSetOwner { unsigned char prefix[0xF0]; int value; int stored; };
void func_0020BDA8(void *self, int *src, int value);
void func_0020C718(struct RefSetOwner *self, int *src, int value)
{
    func_0020BDA8(self, src, value);
    self->value = value;
    self->stored = *src;
}
