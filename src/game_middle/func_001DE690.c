// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Switches the actor to state k (0..23): first leaves the old state, then runs the new state's entry code and restarts
// the clip and the retained resource with the values it chose. Sibling of func_0013E510 (src/engine/actor_state.c).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Clock { float time, step; };
struct Clip { unsigned char prefix[0x64]; float duration; };
struct Runtime { unsigned char prefix[0x14]; struct Clip *clip; unsigned char gap18[4]; float time; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Target { unsigned char prefix[0x1EC]; int word; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x48 - 0x10];
    void *bone48, *bone4C;
    unsigned char gap50[0x1A0 - 0x50];
    qword direction;
    float phase;
    unsigned char gap1B4[4];
    int x1B8;
    unsigned char gap1BC[0x320 - 0x1BC];
    unsigned char context320[0x500 - 0x320];
    unsigned char context500[8];
    int substate;
    unsigned char gap50C[0xE40 - 0x50C];
    unsigned char contextE40[0xF60 - 0xE40];
    unsigned char contextF60[0x1010 - 0xF60];
    unsigned char context1010[0x1108 - 0x1010];
    void *slot1108;
    unsigned char gap110C[0x1134 - 0x110C];
    void *resource1134;
    void *resource1138;
    struct Runtime *runtime;
    void *retained;
    unsigned char gap1144[0x1164 - 0x1144];
    int flag1164;
    unsigned char gap1168[0x1470 - 0x1168];
    unsigned char context1470[4];
    void *clip1474;
    unsigned char gap1478[0x1520 - 0x1478];
    int state;
    float changed;
    unsigned char gap1528[0x1530 - 0x1528];
    void *clip1530;
    unsigned char gap1534[4];
    int x1538;
    unsigned char gap153C[0x155C - 0x153C];
    void *clip155C;
    unsigned char gap1560[0x1568 - 0x1560];
    struct Object *target;
    unsigned char gap156C[0x1574 - 0x156C];
    void *clip1574;
    int x1578;
    void *clip157C;
    void *clip1580;
    unsigned char gap1584[4];
    int x1588;
    unsigned char gap158C[0x1660 - 0x158C];
    void *clip1660;
    void *resource1664;
    unsigned char gap1668[0x1674 - 0x1668];
    int x1674;
    unsigned char gap1678[0x1680 - 0x1678];
    unsigned char context1680[0x18E0 - 0x1680];
    unsigned char context18E0[0xC];
    struct Object *pusher;
    unsigned char gap18F0[0x1A30 - 0x18F0];
    void *prop1A30;
    void *prop1A34;
    unsigned char gap1A38[0x1AC0 - 0x1A38];
    void *clip1AC0;
    void *clip1AC4;
    void *clip1AC8;
    unsigned char gap1ACC[0x1B00 - 0x1ACC];
    int x1B00;
    unsigned char gap1B04[0x1C90 - 0x1B04];
    struct Target *x1C90;
};
struct Pair { unsigned char prefix[4]; void *animation; };
extern struct Clock D_0036BB98;
extern qword D_00317560;
extern char D_003174C0[];
void func_0028F068(struct Actor *self, void *bone, int mode);
void func_00155328(struct Actor *self);
void func_001DF600(struct Actor *self, int state);
void *func_001FE728(void *property, int flag);
void func_001B77F8(void *request, int mode, void *payload);
void func_001B4430(void *context, int mode);
void func_001C21F0(void *context, int mode);
void func_001E1018(struct Actor *self, int mode);
void func_001E16E8(struct Actor *self, int mode);
void func_001E1EB8(struct Actor *self, int mode);
void func_001DDCB8(struct Actor *self, int mode);
void func_001DE398(struct Actor *self, int mode);
void func_002734E8(void *context, int mode);
void func_0023EBF8(struct Actor *self, int flag);
void func_001BFAD0(void *context, int mode);
void func_001E2E88(struct Actor *self, int mode);
void func_001E4900(struct Actor *self, int mode);
void func_001C7A00(struct Actor *self, int a, int b);
int func_00173428(void *slot);
void *func_001733F8(void *slot);
void *func_00173408(void *slot);
int func_00239A78(void *resource, int id);
void func_00155310(struct Actor *self, int flag);
void func_00258F28(void *context);
void func_001BDBB0(void *context, int mode);
void func_001DE4D8(struct Actor *self);
void func_0024E8E8(struct Actor *self, qword offset);
void func_0023D938(struct Actor *self, qword v);
void func_0023D9D0(struct Actor *self, qword v);
void func_00137628(struct Runtime **runtime);
void func_0023AC58(void **retained);
void func_00137588(void *clip, struct Actor *self, int flags, struct Runtime **runtime, float start, float rate);
void func_0023AB98(void *resource, struct Actor *self, int id, int flags, int mask, void **retained);
#define CALL0(p, n) ((void (*)(void *))(p)->methods[n].function)((char *)(p) + (p)->methods[n].adjustment)
#define CALL1(p, n, a) ((void (*)(void *, int))(p)->methods[n].function)((char *)(p) + (p)->methods[n].adjustment, a)
#define INT1(p, n, a) ((int (*)(void *, int))(p)->methods[n].function)((char *)(p) + (p)->methods[n].adjustment, a)
#define INT0(p, n) ((int (*)(void *))(p)->methods[n].function)((char *)(p) + (p)->methods[n].adjustment)
static inline qword Position(void *self)
{
    struct Method *method = &((struct Object *)self)->methods[36];
    return ((qword *(*)(void *))method->function)((char *)self + method->adjustment)[3];
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline int IsActive(void *slot)
{
    return slot && func_00173428(slot) != 0;
}
void func_001DE690(struct Actor *self, int k)
{
    int old;
    void *clip, *resource;
    int flags, id, mask;
    float start, rate;
    if (k == self->state)
        return;
    switch (self->state) {
    case 0:
        func_0028F068(self, self->bone48, 2);
        func_0028F068(self, self->bone4C, 2);
        func_00155328(self);
        break;
    case 17:
    case 18:
        func_0028F068(self, self->bone48, 2);
        func_0028F068(self, self->bone4C, 2);
        break;
    case 3:
        func_001DF600(self, -1);
        break;
    case 2:
        if (!self->flag1164) {
            void *property = 0;
            switch (k) {
            case 0:
            case 1:
            case 4:
            case 5:
            case 10:
            case 12:
            case 13:
                property = self->prop1A30;
                break;
            case 14:
                if (self->substate != 1) {
                    if (self->substate > 0) {
                        if (self->substate < 5)
                            property = self->substate < 3 ? self->prop1A30 : self->prop1A34;
                        else
                            property = self->prop1A30;
                    } else {
                        property = self->prop1A30;
                    }
                }
                break;
            }
            if (property)
                func_001FE728(property, 1);
        }
        func_001B77F8(self->context320, -1, 0);
        break;
    case 14:
        func_001B4430(self->context500, -1);
        break;
    case 15:
        func_001C21F0(self->contextE40, -1);
        break;
    case 12:
        func_001E1018(self, -1);
        break;
    case 13:
        func_001E16E8(self, -1);
        break;
    case 4:
        func_001E1EB8(self, -1);
        break;
    case 5:
        func_001DDCB8(self, -1);
        break;
    case 10:
        func_001DE398(self, -1);
        break;
    case 16:
        CALL0(self->pusher, 9);
        func_002734E8(self->context18E0, -1);
        func_0023EBF8(self, 0);
        break;
    case 1:
    case 11:
        self->phase = self->runtime->time / self->runtime->clip->duration;
        break;
    case 6:
        self->x1674 = 0;
        break;
    case 21:
        func_001BFAD0(self->context1010, -1);
        break;
    case 22:
        func_001E2E88(self, -1);
        self->x1B00 = 0;
        break;
    case 7:
        self->target = 0;
        break;
    case 23:
        func_001E4900(self, -1);
        func_0023EBF8(self, 0);
        self->x1B8 = 0;
        func_001C7A00(self, 0, 0);
        break;
    }
    old = self->state;
    self->state = k;
    clip = 0;
    resource = 0;
    flags = 1;
    id = -1;
    mask = 4;
    start = 0.0f;
    rate = 1.0f;
    self->changed = D_0036BB98.time;
    switch (k) {
    case -1:
        break;
    case 0:
        func_0028F068(self, self->bone48, 1);
        func_0028F068(self, self->bone4C, 1);
        if (IsActive(self->slot1108))
            resource = func_001733F8(self->slot1108);
        if (!resource)
            resource = self->resource1134;
        self->direction = D_00317560;
        if (old != 2)
            id = old != 11 ? 0x192 : 0x193;
        else
            id = 0x195;
        if (func_00239A78(resource, id) < 0)
            id = -1;
        mask = INT0(self, 111);
        func_00155310(self, 1);
        break;
    case 1:
        clip = self->clip1474;
        func_00258F28(self->context1470);
        flags = 9;
        break;
    case 15:
        func_001BDBB0(self->contextF60, -1);
        break;
    case 3:
        func_001DF600(self, 0);
        clip = self->clip1AC8 && self->x1538 ? self->clip1AC8 : self->clip1530;
        break;
    case 5:
        func_001DDCB8(self, 0);
        CALL0(self, 101);
        return;
    case 6:
        resource = self->resource1664;
        break;
    case 4:
        switch (self->x1588) {
        case 0:
            clip = self->clip157C;
            break;
        case 1:
            clip = self->clip1580;
            break;
        }
        self->direction = D_00317560;
        func_001E1EB8(self, 0);
        break;
    case 7:
        clip = self->clip1AC0 && INT1(self, 113, 0x13) ? self->clip1AC0 : self->clip155C;
        self->direction = D_00317560;
        func_001DE4D8(self);
        if (self->target)
            func_0024E8E8(self, Sub(Position(self->target), Position(self)));
        break;
    case 9:
        clip = self->clip1660;
        self->direction = D_00317560;
        break;
    case 8:
        clip = self->clip1AC4 && self->x1578 ? self->clip1AC4 : self->clip1574;
        self->direction = D_00317560;
        break;
    case 10:
        func_001DE398(self, 0);
        CALL0(self, 101);
        return;
    case 11: {
        struct Pair *pair = 0;
        if (IsActive(self->slot1108))
            pair = func_00173408(self->slot1108);
        if (!pair)
            pair = (struct Pair *)self->context1680;
        flags = 9;
        clip = pair->animation;
        func_00258F28(pair);
        break;
    }
    case 16:
        CALL0(self->pusher, 8);
        func_002734E8(self->context18E0, 0);
        func_0023EBF8(self, 1);
        ((void (*)(void *, qword))self->methods[40].function)((char *)self + self->methods[40].adjustment, D_00317560);
        return;
    case 17:
        resource = self->resource1138;
    case 18:
        func_0028F068(self, self->bone48, 1);
        func_0028F068(self, self->bone4C, 1);
        self->direction = D_00317560;
        break;
    case 21:
        func_001BFAD0(self->context1010, 0);
        return;
    case 22:
        func_001E2E88(self, 0);
        CALL0(self, 101);
        return;
    case 23:
        func_0023EBF8(self, 1);
        self->x1B8 = 2;
        ((void (*)(void *, int, void *))self->methods[43].function)((char *)self + self->methods[43].adjustment, self->x1C90->word, D_003174C0);
        ((void (*)(void *, void *, int, int))self->methods[10].function)((char *)self + self->methods[10].adjustment, self->x1C90, self->x1C90->word, 3);
        func_0023D938(self, D_00317560);
        func_0023D9D0(self, D_00317560);
        func_001E4900(self, 0);
        CALL0(self, 101);
        return;
    }
    func_00137628(&self->runtime);
    func_0023AC58(&self->retained);
    func_00137588(clip, self, flags, &self->runtime, start, rate);
    func_0023AB98(resource, self, id, flags, mask, &self->retained);
    CALL0(self, 101);
}
