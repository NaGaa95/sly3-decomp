// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct AllocRequest { int bytes; int alignment; AllocRequest(int b, int a) { bytes = b; alignment = a; } };
extern "C" void func_001D2798(void *frame, int flags);
extern "C" void func_001A2D30(void *stream, int flags);
class FrameGuard {
    int storage[4];
public:
    FrameGuard() __asm__("func_001D2770");
    ~FrameGuard() { func_001D2798(this, 2); }
};
struct MemoryStream { unsigned char storage[0x64]; };
extern "C" void *func_001A2C88(MemoryStream *stream, int bytes, void *buffer, int flags);
struct Key {
    unsigned int low; unsigned int high; int mode; unsigned char flags;
    void SetMode(int m) { mode = m; }
};
struct Entry { unsigned char prefix[0x48]; int mode; unsigned char gap4C[4]; int stamp; };
struct Node { unsigned char prefix[0x40]; struct Entry *entry; int threshold; int value; struct Node *next; };
struct Save { unsigned int word0; unsigned int word4; unsigned char gap8[0x34 - 8]; unsigned int word34; unsigned char gap38[4]; unsigned int word3C; unsigned char gap40[4]; int result44; int result48; };
struct Owner { unsigned char prefix[0xB0]; struct Save *save; };
struct Globals { unsigned char prefix[0xC]; int value; };
extern "C" {
extern struct Node *D_004797A8;
extern int D_0036C650;
extern struct Globals D_0047A4A0;
extern char D_00327F08[];
void *func_001D25B0(struct AllocRequest *request);
void func_002BC568(struct Key *key);
int func_001A3118(void *stream, struct Key *key);
void func_00118E10(void *stream, int count, unsigned char *buffer);
int func_00118FF8(void *stream);
int func_00119048(void *stream);
int func_002920F0(const void *a, const void *b, int count);
void func_00261070(struct Entry *entry, int flag);
void func_00263118(struct Owner *owner, void *stream);
void func_002631C8(struct Owner *owner, void *stream);
}
extern "C" void func_00260A60(struct Owner *owner)
{
    int maximum = 0;
    struct Node *node;
    for (node = D_004797A8; node; node = node->next) {
        struct Entry *entry = node->entry;
        if (entry->mode) {
            if (entry->mode != 1 || D_0036C650 - entry->stamp < 2) {
                if (maximum < node->value)
                    maximum = node->value;
            }
        }
    }
    for (node = D_004797A8; node; node = node->next) {
        struct Entry *entry = node->entry;
        if (!(node->threshold < maximum)) {
            if (entry->mode)
                func_00261070(entry, 0);
        }
    }
    D_0047A4A0.value = maximum;
    FrameGuard frame;
    void *buffer;
    {
        AllocRequest request(0x10000, 0x40);
        buffer = func_001D25B0(&request);
    }
    MemoryStream storage;
    MemoryStream *stream = &storage;
    func_001A2C88(stream, 0x10000, buffer, 0);
    Key key;
    char name[0x100];
    int ok;
    key.SetMode(2);
    func_002BC568(&key);
    if (!owner->save)
        ok = 0;
    else {
        unsigned int high = owner->save->word4 ^ owner->save->word3C;
        unsigned int low = (owner->save->word0 ^ owner->save->word34) + 0xCA0;
        key.SetMode(2);
        key.low = low;
        key.high = high;
        ok = high != 0;
    }
    unsigned char magic[4];
    int version;
    if (!ok || !func_001A3118(stream, &key) ||
        (func_00118E10(stream, 0x4000, (unsigned char *)0x70000000),
         magic[0] = func_00118FF8(stream),
         magic[1] = func_00118FF8(stream),
         magic[2] = func_00118FF8(stream),
         magic[3] = func_00118FF8(stream),
         version = func_00119048(stream),
         func_002920F0(magic, D_00327F08, 4) || version != 7))
    {
        func_001A2D30(stream, 2);
        return;
    }
    owner->save->result44 = D_0047A4A0.value;
    func_00263118(owner, stream);
    func_002631C8(owner, stream);
    owner->save->result48 = D_0047A4A0.value;
    func_001A2D30(stream, 2);
}
