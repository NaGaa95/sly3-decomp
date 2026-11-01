// Draw the label of every panel entry whose id matches one of the three query slots: build the text, render it at the entry position and release the temporary block frame (Sly 2 func_001DAC58).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Text { float x, y, dx, dy; unsigned char pad[0x10]; };
struct Font { unsigned char data[0x1B0]; };
struct AllocationRequest { int bytes, alignment; };
struct Slot { int id, a, b; };
struct Query { unsigned char pad[0x1250]; Slot slots[3]; };
struct Entry { int id; unsigned char pad[0x10]; float x, y; unsigned char pad1C[4]; };
struct Panel {
    unsigned char pad[0x34];
    void *owner;
    unsigned char pad38[0x5C - 0x38];
    int count;
    Entry *entries;
};
class BlockFrame {
    int storage[4];
public:
    BlockFrame() __asm__("func_001D2770");
    ~BlockFrame();
};
extern "C" void func_001D2798(void *frame, int flags);
inline BlockFrame::~BlockFrame() { func_001D2798(this, 2); }
extern unsigned char D_00475480[];
extern float D_0034904C;
extern unsigned short *D_00349050[];
extern "C" {
int func_00261BD0(void *);
Query *func_001F4AD0(void *game, int a);
int func_0013B500(void *, int);
void func_002BC878(Text *, float, float);
void func_002BC888(Text *, float, float);
void func_002BC898(Text *, unsigned int *);
void func_002BC8B0(Text *, int);
void func_002BC8B8(Text *, int);
int func_002715F8(unsigned short *);
void *func_001D25B0(unsigned int *);
void func_002717E0(void *, unsigned short *);
void func_00264880(Font *, void *, float);
void func_00265480(Font *, Text *, int);
}
extern "C" void func_0021F118(Panel *panel)
{
    Query *query;
    int i;
    if (!panel->owner)
        return;
    if (!func_00261BD0(panel->owner))
        return;
    query = func_001F4AD0(D_00475480, 0);
    if (!query)
        return;
    if (!func_0013B500(query, 0x33))
        return;
    for (i = 0; i < panel->count; i++) {
        Entry *entry = &panel->entries[i];
        int j;
        for (j = 0; j < 3; j++) {
            if (entry->id == query->slots[j].id) {
                Text text;
                unsigned int scratch[2];
                void *buffer;
                func_002BC878(&text, 0.0f, 0.0f);
                func_002BC888(&text, 640.0f, 480.0f);
                unsigned int *words = scratch;
                scratch[0] = 0xFF808080;
                func_002BC898(&text, words);
                func_002BC8B0(&text, 0);
                func_002BC8B8(&text, 0);
                BlockFrame frame;
                scratch[0] = func_002715F8(D_00349050[j]) * 2 + 2;
                words[1] = 0x10;
                buffer = func_001D25B0(words);
                func_002717E0(buffer, D_00349050[j]);
                Font font;
                func_00264880(&font, buffer, D_0034904C);
                {
                    float x = entry->x;
                    float y = entry->y;
                    text.x = x;
                    text.y = y;
                    text.dx = 50.0f;
                    text.dy = 50.0f;
                }
                func_00265480(&font, &text, 0x23);
                break;
            }
        }
    }
}
