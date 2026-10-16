// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct FrameMethod {
    short adjustment,reserved;
    void (*update)(void *);
};

struct FrameObject {
    char unaccessed[0xC];
    struct FrameMethod *methods;
};

struct FrameRecord {
    unsigned int flags;
    struct FrameObject *object;
};

struct PendingFrameNode {
    char unaccessed[0x78];
    struct PendingFrameNode *next;
};

struct FrameGame {
    char unaccessed[0x44F8];
    int currentIdentifier;
    unsigned int tick;
    int cachedIdentifier;
    char unaccessed4504[0x4648-0x4504];
    int count;
    int reserved464C;
    int *currentIndex;
    struct FrameRecord *records;
    char unaccessed4658[0x480C-0x4658];
    struct PendingFrameNode *pending;
};

struct S;
struct G;
struct Slot;
extern struct Slot *D_00468D00;
extern char D_00447B00[];
extern char D_0046F7A0[],D_0036C2E0[],D_0036C308[];
void func_001C5E08(struct S *game);
void func_00209BA0(struct G *game);
void func_00202E58(void *node);
void func_001A77F0(void);
void func_0021F118(void *queue);
void func_001746A8(void *record);

void func_00209C40(struct FrameGame *game)
{
    struct PendingFrameNode *node;
    int index;

    func_001C5E08((struct S *)game);
    ++game->tick;
    D_00468D00=(struct Slot *)D_00447B00;
    if(game->currentIdentifier!=game->cachedIdentifier) {
        game->cachedIdentifier=game->currentIdentifier;
        func_00209BA0((struct G *)game);
    }

    game->currentIndex=&index;
    for(index=0;index<game->count;++index) {
        struct FrameRecord *record=&game->records[index];
        if((record->flags&0x108)==8) {
            struct FrameObject *object=record->object;
            struct FrameMethod *method=&object->methods[21];
            method->update((char *)object+method->adjustment);
        }
    }
    game->currentIndex=0;

    for(node=game->pending;node;node=node->next)
        func_00202E58(node);
    func_001A77F0();
    func_0021F118(D_0046F7A0);
    func_001746A8(D_0036C2E0);
    func_001746A8(D_0036C308);
}
