// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct StartMethod { short adjustment, word2; void *function; };
struct StartTable {
    unsigned char prefix[0x120];
    struct StartMethod position;
    unsigned char gap128[0x318 - 0x128];
    struct StartMethod notify;
};
struct StartPosition { unsigned char prefix[0x30]; qword value; };
struct StartTarget { unsigned char prefix[0xC]; struct StartTable *methods; };
struct StartActor {
    unsigned char prefix[0xC];
    struct StartTable *methods;
    unsigned char gap10[0x178 - 0x10];
    int mode;
    unsigned char gap17C[0x18C - 0x17C];
    struct StartTarget *target;
};
struct StartEvent { unsigned char prefix[0x50]; unsigned int flags; };
extern unsigned char D_00475480[];
void func_001A1A28(struct StartActor *actor, int mode);
void func_00173E00(void *world, int first, qword position, void *actor);
void func_001BDBB0(void *record, int value);
int func_001A1CB8(struct StartActor *actor, struct StartEvent *event)
{
    if (actor->mode != 3 && (event->flags & 2)) {
        func_001A1A28(actor, 3);
        {
            struct StartMethod *position = &actor->methods->position;
            func_00173E00(D_00475480, 0,
                          ((struct StartPosition *(*)(void *))position->function)((char *)actor + position->adjustment)->value, actor);
        }
        if (actor->target) {
            struct StartTarget *target;
            struct StartMethod *notify;
            func_001BDBB0((char *)actor->target + 0xF60, -1);
            target = actor->target;
            notify = &target->methods->notify;
            ((void (*)(void *, int))notify->function)((char *)target + notify->adjustment, 0);
        }
        return 1;
    }
    return 0;
}
