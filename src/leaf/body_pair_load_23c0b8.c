// SLY3_CFLAGS: -Os -G0
// Load a two-body constraint object from a binary stream: base initializer, global set, then count 0xD0-byte elements (shape built
// through virtual slot 55, flag bits read as bytes, a box with its transformed copy and tree), spare elements marked kind 10, the
// shared record, and the tagged link flag at +0x3C. The elements are the ones processed by func_0023C970.
struct Stream;
struct Box { float v[6]; };
struct VTE { short d; short p; void *(*fn)(void *, ...); };
struct Request { int bytes; int alignment; };
struct Elem {
    void *shape; struct Self *owner; float f8; int pad0C; int x10; int active;
    struct { unsigned long kind : 16; unsigned long b16 : 1; unsigned long b17 : 1; unsigned long b18 : 1; unsigned long b19 : 1; unsigned long b20 : 1; unsigned long b21 : 1; unsigned long pad22 : 10; unsigned long x1C : 32; } fl;
    int x20; char pad24[0x78 - 0x24]; char x78[0x10]; struct Box box; struct Box box2; char padB8[0xD0 - 0xB8];
};
struct Record { char pad[0xD0]; float f; char padD4[0xE0 - 0xD4]; };
struct Self {
    char pad0[0xC]; struct VTE *vt; char pad10[0x3C - 0x10]; unsigned link3C; char pad40[0x70 - 0x40]; char set70[0x38];
    int xA8; char padAC[0xD0 - 0xAC]; int count; struct Elem *elems; struct Record *record;
};
extern char D_0034A160[];
void func_0028C338(struct Self *, struct Stream *);
unsigned func_001190A8(struct Stream *);
void func_0018D148(void *, struct Self *, struct Stream *);
int func_00119178(struct Stream *);
int func_001191E0(struct Stream *);
int func_00119128(struct Stream *);
float func_00119260(struct Stream *);
void func_001193F8(struct Stream *, struct Box *);
void func_0018AFB0(struct Box *, void *, struct Box *);
void func_00119640(struct Stream *, struct Box *, void *);
int func_00119048(struct Stream *);
void func_0023B9C8(struct Self *);
void *func_001D2538(struct Request *);
void func_001192F8(struct Stream *, struct Record *);
void func_0023C4D0(struct Self *, float);
void func_001519C8(struct Self *, struct Stream *);
void func_0023B3A8(struct Self *);
void func_00151D80(struct Self *, struct Stream *, void *);
void func_001C9198(struct Self *, int);
void func_0023C0B8(struct Self *self, struct Stream *stream)
{
    struct Request request;
    struct Elem *e;
    unsigned type;
    int extra;
    int i;
    int n;
    int id;
    func_0028C338(self, stream);
    type = func_001190A8(stream);
    i = 0;
    func_0018D148(self->set70, self, stream);
    extra = (int)self->vt[67].fn((char *)self + self->vt[67].d);
    n = func_00119178(stream);
    request.alignment = 16;
    self->count = n;
    request.bytes = (n + extra) * 0xD0;
    self->elems = (struct Elem *)func_001D2538(&request);
    for (i = 0; i < self->count; i++) {
        e = &self->elems[i];
        e->owner = self;
        id = func_00119178(stream);
        e->shape = self->vt[55].fn((char *)self + self->vt[55].d, id);
        e->x10 = func_001191E0(stream);
        e->fl.b16 = func_00119128(stream);
        e->fl.b17 = func_00119128(stream);
        e->f8 = func_00119260(stream);
        e->fl.b18 = func_00119128(stream);
        func_001193F8(stream, &e->box);
        if (e->shape == 0) {
            e->shape = D_0034A160;
            e->box2 = e->box;
        } else {
            func_0018AFB0(&e->box, 0, &e->box2);
        }
        func_00119640(stream, &e->box2, e->x78);
        e->fl.x1C = func_001190A8(stream);
        e->fl.kind = func_00119048(stream);
        e->fl.b21 = func_00119128(stream);
        e->x20 = func_00119178(stream);
        e->fl.b19 = func_00119128(stream);
    }
    for (i = self->count; i < self->count + extra; i++) {
        e = &self->elems[i];
        e->fl.kind = 10;
    }
    func_0023B9C8(self);
    if (self->count > 0) {
        struct Record *r;
        request.bytes = 0xE0;
        request.alignment = 16;
        r = (struct Record *)func_001D2538(&request);
        self->record = r;
        r->f = func_00119260(stream);
        func_001192F8(stream, r);
        func_0023C4D0(self, 1.0f);
        self->vt[68].fn((char *)self + self->vt[68].d);
    }
    func_001519C8(self, stream);
    if (self->xA8) {
        if (((self->link3C ^ 1) & 1) != 0)
            *(unsigned *)self->link3C |= 8;
        else
            self->link3C |= 8;
    }
    func_0023B3A8(self);
    func_00151D80(self, stream, 0);
    func_001C9198(self, type);
}
