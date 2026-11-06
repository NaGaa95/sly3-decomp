// Per-frame state machine of the target tracker: wait/advance through states 2..8 (re-evaluated until the state settles), and while in state 1 pick up nearby busy-free items within 60000 units (squared XY distance test) and hand them over.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { short d; short pad; void *pfn; } VTE;
struct Item {
    unsigned char pad00[0xC];
    VTE *vt;
    unsigned char pad10[0x1B8 - 0x10];
    int mode;
    unsigned char pad1BC[0x1C8 - 0x1BC];
    int group;
    unsigned char pad1CC[0x518 - 0x1CC];
    int busy;
};
struct Target { unsigned char pad[0x48]; int state; };
struct Self {
    unsigned char pad00[0x40];
    struct Item *anchor;
    struct Item *items[5];
    int count;
    int state;
    unsigned char pad60[4];
    float stateTime;
    unsigned char pad68[0x94 - 0x68];
    int limit;
    int counter;
    unsigned char pad9C[0xA4 - 0x9C];
    struct Target *target;
};
extern struct { unsigned char pad[0x40]; float t40; } D_0036BB98;
extern unsigned char D_003751D0[];
extern unsigned char D_0046FBE0[];
void func_001C8168(struct Self *self);
void func_00219A18(struct Self *self, int state);
int func_0021DD30(void *object);
int func_001A7980(int button);
int func_00260758(void *target, int id);
void func_00215FD0(struct Item *item, int flag);
void func_002412C8(struct Item *item, float value);
void func_0021A450(struct Self *self, struct Item *item);
#define MATRIX_POSITION(o) (*(qword *)((char *)((void *(*)(void *))(o)->vt[36].pfn)((char *)(o) + (o)->vt[36].d) + 0x30))
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline float LengthSquaredXY(qword v)
{
    qword d;
    float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
void func_00219768(struct Self *self)
{
    int state;
    func_001C8168(self);
    do {
        state = self->state;
        switch (state) {
        case 2:
            if (self->target->state != 3) func_00219A18(self, 3);
            break;
        case 3:
            if (D_0036BB98.t40 - self->stateTime > 1.0f) func_00219A18(self, 4);
            break;
        case 4:
            if (D_0036BB98.t40 - self->stateTime > 1.0f) func_00219A18(self, 5);
            break;
        case 5:
            self->counter++;
            if (self->counter >= self->limit) func_00219A18(self, 6);
            else func_00219A18(self, 3);
            break;
        case 6:
            if (func_0021DD30(D_003751D0)) break;
            if (func_0021DD30(D_0046FBE0)) break;
            if (func_001A7980(0xF0)) func_00219A18(self, 7);
            break;
        case 7:
            if (func_00260758(self->target, 0x378)) break;
            func_00219A18(self, 8);
            break;
        case 8:
            func_00219A18(self, 0);
            break;
        }
    } while (self->state != state);
    if (self->state == 1) {
        int i;
        for (i = 0; i < self->count; i++) {
            struct Item *item = self->items[i];
            if (item->mode == 2 && item->group != 5 && !item->busy) {
                qword here = MATRIX_POSITION(self->anchor);
                if (LengthSquaredXY(Sub(here, MATRIX_POSITION(item))) > 3.6e9f) {
                    func_00215FD0(item, 1);
                    func_002412C8(item, 1.0f);
                    func_0021A450(self, item);
                }
            }
        }
    }
}
