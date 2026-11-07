// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Load the pending world request and restore actor and view state (cf. Sly 2 src/hand/func_0020E890.cpp).
struct HEADER { int words[16]; };
struct REQUEST { int flags; HEADER header; int extra; };
struct KEY { int name, tag, kind; char data[0x104]; };
struct VT { short delta, unused; void *function; };
struct ACTOR { char pad0[0xC]; VT *vtable; };
struct SW {
    char pad0[0x3EB8]; int actorCount; ACTOR *actors[1];
    char pad3EC0[0x4344 - 0x3EC0]; int pending; REQUEST request; int pending2; REQUEST request2; HEADER current;
    char pad441C[0x4F60 - 0x441C]; float resumeTime;
};
struct STREAM { unsigned char storage[0x70]; };
class CTX {
    int storage[4];
public:
    CTX() __asm__("__3CTX");
    ~CTX() __asm__("_$_3CTX");
};
extern float g_clock;
extern int D_00389AC0;
extern char D_0038AF00[], D_00475480[], D_0036BC10[], D_0036C700[], D_0036C6E8[], D_0046F540[], D_004C4090[], D_00370AF0[];
extern "C" {
HEADER *func_0025E070(int);
void func_002BC568(KEY *);
void func_00183668(int);
void func_001F1430(int);
void func_001A2C88(STREAM *, int, void *, int);
int func_001A3118(STREAM *, KEY *);
void func_001A2D30(STREAM *, int);
void SetDecompress(STREAM *, int, void *) __asm__("SetDecompress__18CBinaryInputStreamiPUc");
void func_001A3058(STREAM *);
void func_0025AE60(SW *);
void func_001653E0(float *);
void *memset(void *, int, unsigned int);
void func_0025A628(void *);
int func_001DBDB8(int *);
void func_00168FE0(void *);
int func_0025E098(HEADER *);
void func_0025DFB0(SW *, int);
void func_0025AFD8(SW *);
void func_0014F440(SW *, STREAM *);
void func_001A30A8(STREAM *);
void func_0025B860(SW *);
void func_0025BDD0(SW *);
void func_00184AA0(void *);
void func_001FC458(SW *);
void func_00185420(SW *, float);
void func_00189118(void *);
void func_0021D948(void *);
void func_0025B9C0(SW *);
void func_00166548(ACTOR *);
void func_00184B60(void *);
void func_001F15C0(int);
void func_0025C128(SW *);
void func_00288FB0(void *);
void func_001C6F30(void *);
}
static inline int Same(const HEADER &ra, const HEADER *b)
{
    const HEADER *a = &ra;
    if (a == b)
        return 1;
    if (!b)
        return 0;
    return (a->words[2] ^ a->words[14]) == (b->words[2] ^ b->words[14]);
}
static inline void Call(ACTOR *actor)
{
    VT *entry = &actor->vtable[18];
    ((void (*)(void *))entry->function)((char *)actor + entry->delta);
}
extern "C" void func_0025C2A8(SW *p)
{
    if (!p->pending)
        return;
    if (p->pending2) {
        p->request = p->request2;
        p->pending2 = 0;
    }
    if (p->request.flags & 0x40)
        D_00389AC0 = 0;
    REQUEST request = p->request;
    REQUEST *destination = &p->request;
    p->pending = 0;
    float resume;
    if ((request.flags & 0xD5) || Same(request.header, func_0025E070(0)))
        resume = 0.0f;
    else {
        float remaining = p->resumeTime - g_clock;
        resume = remaining > 0.0f ? remaining : 0.0f;
    }
    int changed = 0;
    int hasFile = request.header.words[1] != request.header.words[15];
    if (!Same(request.header, &p->current) || D_00389AC0 > 0 || !hasFile)
        changed = 1;
    if (request.flags & 2)
        changed = 1;
    KEY key;
    KEY *keyPointer = &key;
    keyPointer->kind = 2;
    func_002BC568(keyPointer);
    if (hasFile) {
        int name = (request.header.words[0] ^ request.header.words[13]) + 0xCA0;
        int tag = request.header.words[1] ^ request.header.words[15];
        keyPointer->kind = 2;
        key.name = name;
        key.tag = tag;
        if (!tag)
            return;
    }
    if (changed) {
        func_00183668(1);
        func_001F1430(2);
        STREAM stream;
        func_001A2C88(&stream, 0xD7C00, D_0038AF00, 0);
        if (hasFile && !func_001A3118(&stream, keyPointer)) {
            func_001A2D30(&stream, 2);
            return;
        }
        SetDecompress(&stream, 0x4000, (void *)0x70000000);
        func_001A3058(&stream);
        func_0025AE60(p);
        func_001653E0(&g_clock);
        memset(D_00475480, 0, 0x5000);
        memset(D_00475480, 0, 0x5000);
        func_0025A628(D_00475480);
        if (func_001DBDB8(&D_00389AC0))
            changed = 1;
        func_00168FE0(D_0036BC10);
        p->current = request.header;
        *destination = request;
        func_0025DFB0(p, func_0025E098(&p->current));
        func_0025AFD8(p);
        {
            CTX ctx;
            if (hasFile) {
                func_0014F440(p, &stream);
                func_001A30A8(&stream);
            }
            func_0025B860(p);
        }
        func_001A2D30(&stream, 2);
    } else {
        func_0025BDD0(p);
    }
    func_00184AA0(D_0036C700);
    func_001FC458(p);
    if (resume > 0.0f)
        func_00185420(p, resume);
    func_00189118(D_0036C6E8);
    func_0021D948(D_0046F540);
    if (hasFile) {
        func_0025B9C0(p);
        for (int i = 0; i < p->actorCount; i++) {
            ACTOR *actor = p->actors[i];
            Call(actor);
            func_00166548(actor);
        }
        func_00184B60(D_0036C700);
    }
    if (changed)
        func_001F15C0(2);
    func_0025C128(p);
    func_00288FB0(D_004C4090);
    if (!hasFile)
        func_001C6F30(D_00370AF0);
}
