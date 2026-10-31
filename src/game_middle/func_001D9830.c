// SLY3_CFLAGS: -Os -G0
struct Clock { float time; };
struct Link { unsigned char prefix[0x10]; void *key; };
struct Node { unsigned char prefix[0xDC]; struct Link *link; };
struct Context { unsigned char prefix[0xD8]; struct Node *node; };
struct Owner {
    unsigned char prefix0[0x110];
    int mode;
    unsigned char gap114[4];
    void *key;
};
struct Phase {
    unsigned char prefix0[0x10];
    struct Context *context;
    unsigned char gap14[4];
    void *target;
    unsigned char gap1C[0x30 - 0x1C];
    struct Owner *owner;
    unsigned char gap34[4];
    int state;
    unsigned char gap3C[4];
    float deadline;
};
extern struct Clock D_0036BB98;
void func_002389A0(struct Phase *self);
int func_00238AD0(struct Phase *self);
int func_001D99B0(struct Phase *self);
void func_001D9940(struct Phase *self);
void func_001D9A88(struct Phase *self, int flag);
int func_001D8AC0(void *target);

void func_001D9830(struct Phase *self)
{
    func_002389A0(self);
    switch (self->state) {
    case -1:
        break;
    case 1:
        if (func_00238AD0(self))
            func_001D9940(self);
        break;
    case 0:
        switch (self->owner->mode) {
        case 1:
            if (func_00238AD0(self)) {
                if (func_001D99B0(self))
                    func_001D9940(self);
                else
                    func_001D9A88(self, 1);
            }
            break;
        case 0:
            if (self->deadline < D_0036BB98.time) {
                func_001D9A88(self, 1);
            } else {
                struct Node *node = self->context->node;
                struct Link *link = node ? node->link : 0;
                void *key = link ? link->key : 0;
                if (key == self->owner->key && func_001D8AC0(self->target))
                    func_001D9940(self);
            }
            break;
        }
        break;
    }
}
