// SLY3_CFLAGS: -Os -G0
// Clone method of the two-body constraint object (pairs with func_0023C0B8/func_0023C970): copy the base object, then duplicate the
// per-element sub-objects (virtual slot 56 copies each sub-object from the source), re-link owner pointers of the 0x100-byte records
// by kind (4, 14, 16, 17), rebuild each record's child list in reverse order, duplicate the 0xD0-byte elements with their mesh
// arrays and the shared record, bump the share count and refresh the bounds.
typedef unsigned long ulong;
struct VTE { short d; short p; void (*fn)(void *, void *, void *); };
struct VTI { short d; short p; int (*fn)(void *); };
struct REQUEST { int bytes, alignment; };
struct VEC3 { float x, y, z; };
struct Self;
struct Node { char pad0[0x10]; struct Node *next; };
struct Holder { struct Holder *self0; struct Holder *a4; char pad8[0x30 - 8]; struct Holder *a30; char pad34[0xA8 - 0x34]; struct Holder *backA8; };
struct Group { int count; struct Part *parts; char pad8[0x60 - 8]; struct Group *group60; };
struct Part { char pad0[0x60]; struct Group *group; struct Holder *held; char pad68[0x70 - 0x68]; };
struct BigElem {
    char pad0[0x90]; struct Node *list; char pad94[0x98 - 0x94]; short kind; char pad9A[0xA0 - 0x9A]; char xA0[8]; void *held; char padAC[0x100 - 0xAC];
};
struct Mesh { void *p0; void *p4; void *p8; void *pC; };
struct Elem {
    char pad0[4]; struct Self *owner; char pad8[0x14 - 8]; struct Mesh *mesh; char pad18[0x70 - 0x18];
    char x70[8]; char x78[0x10]; int count88; int pad8C; int count90; char pad94[0xA0 - 0x94]; char xA0[0x30];
};
struct Rec { char pad[0xDC]; struct Rec2 *rec2; };
struct Rec2 { struct Self *owner; char pad[0x70 - 4]; };
struct Self {
    char pad0[0xC]; union { struct VTE *vt; struct VTI *vtI; }; char pad10[0x28 - 0x10]; char pad28[7]; unsigned long flags : 8; char pad30[0x40 - 0x30]; int count; struct BigElem *bigs; char x48[4]; char x4C[4]; char x50[4]; struct VEC3 pos54;
    struct Group *x60; char pad64[0x70 - 0x64]; char x70[0xD0 - 0x70]; int count2; struct Elem *elems; struct Rec *rec; void *xDC; char padE0[0x100 - 0xE0];
    int *refcount; char pad104[0x10C - 0x104]; int x10C;
};
void func_001C8BF0(struct Self *, struct Self *);
void *func_001D24D0(struct REQUEST *, void *);
void *func_001D25B0(struct REQUEST *);
void *func_001D2770(void *);
void func_001D2798(void *, int);
void *func_00130968(struct Node *, struct Self *, struct BigElem *);
void func_0028ECE0(struct Self *, struct BigElem *, void *);
void func_00194B20(void *, struct Self *, struct Self *);
void func_0011AF50(void *);
void func_0018AFB0(void *, void *, void *);
void func_00119D00(void *, void *, void *, void *);
void func_0023B9C8(struct Self *);
void func_0023B3A8(struct Self *);
extern char D_0034A160[];
static inline void *Copy(struct REQUEST *request, int bytes, void *source)
{
    request->bytes = bytes;
    request->alignment = 16;
    return func_001D24D0(request, source);
}
static inline void *Scratch(struct REQUEST *request, int bytes)
{
    request->bytes = bytes;
    request->alignment = 16;
    return func_001D25B0(request);
}
#define CLONE(self, src, dst) ((self)->vt[56].fn)((char *)(self) + (self)->vt[56].d, (src), (dst))

void func_0023F400(struct Self *self, struct Self *src)
{
    struct VEC3 saved;
    struct REQUEST request;
    struct Group *group;
    void *other;
    int i, j, k;
    struct BigElem *big;
    struct Elem *e;
    other = self->xDC;
    group = self->x60;
    saved = self->pos54;
    func_001C8BF0(self, src);
    i = 0;
    self->xDC = other;
    self->pos54 = saved;
    self->x60 = group;
    self->x10C = 0;
    self->bigs = (struct BigElem *)Copy(&request, self->count << 8, self->bigs);
    for (i = 0; i < self->count; i++) {
        big = (struct BigElem *)((char *)self->bigs + (i << 8));
        CLONE(self, src, (char *)big + 0xA0);
        switch (big->kind) {
        case 4:
            CLONE(self, src, (char *)big + 0xA8);
            break;
        case 14: {
            struct Holder *hold;
            hold = (struct Holder *)Copy(&request, 0xE0, big->held);
            CLONE(self, src, hold);
            CLONE(self, src, (char *)hold + 4);
            CLONE(self, src, (char *)hold + 0x30);
            CLONE(self, src, (char *)hold + 0x80);
            hold->a4->backA8 = hold;
            hold->a30->backA8 = hold;
            break;
        }
        case 16: {
            struct Holder *hold;
            hold = (struct Holder *)Copy(&request, 16, big->held);
            big->held = hold;
            if (hold->self0 != (struct Holder *)D_0034A160)
                CLONE(self, src, hold);
            CLONE(self, src, (char *)hold + 4);
            break;
        }
        case 17:
            group = ((struct Part *)big->held)->group;
            if (big->held == (void *)group->parts) {
                group = (struct Group *)Copy(&request, 0x50, group);
                group->parts = (struct Part *)Copy(&request, group->count * 0x70, group->parts);
                for (j = 0; j < group->count; j++) {
                    struct Part *part = &group->parts[j];
                    part->group = group;
                    CLONE(self, src, (char *)part + 0x64);
                    part->held->backA8 = (struct Holder *)part;
                }
            }
            break;
        }
        if (big->list) {
            struct Node *node = big->list;
            struct Node **array;
            char scope[0x10];
            int count = 0;
            int n;
            struct Node **p;
            do { count++; node = node->next; } while (node);
            func_001D2770(scope);
            array = (struct Node **)Scratch(&request, count * 4);
            p = array;
            node = big->list;
            while (node) { *p++ = node; node = node->next; }
            big->list = 0;
            for (n = count - 1; n >= 0; n--) {
                void *clone = func_00130968(array[n], self, big);
                func_0028ECE0(self, big, clone);
            }
            func_001D2798(scope, 2);
        }
    }
    CLONE(self, src, self->x48);
    CLONE(self, src, self->x4C);
    CLONE(self, src, self->x50);
    func_00194B20(self->x70, self, src);
    self->elems = (struct Elem *)Copy(&request, (self->count2 + ((int (*)(void *))self->vtI[67].fn)((char *)self + self->vtI[67].d)) * 0xD0, self->elems);
    for (k = 0; k < self->count2; k++) {
        e = &self->elems[k];
        CLONE(self, src, e);
        e->owner = self;
        func_0011AF50(e->x70);
        func_0018AFB0(e->xA0, 0, e->xA0);
        func_00119D00(src->elems[k].x78, src->elems[k].xA0, e->x78, e->xA0);
        if (e->mesh) {
            e->mesh = (struct Mesh *)Copy(&request, 16, e->mesh);
            e->mesh->p4 = Copy(&request, e->count88 << 4, e->mesh->p4);
            e->mesh->p8 = Copy(&request, e->count88 << 4, e->mesh->p8);
            e->mesh->pC = Copy(&request, e->count90 * 12, e->mesh->pC);
        }
    }
    if (self->rec) {
        self->rec = (struct Rec *)Copy(&request, 0xE0, self->rec);
        if (self->rec->rec2) {
            self->rec->rec2 = (struct Rec2 *)Copy(&request, 0x70, self->rec->rec2);
            self->rec->rec2->owner = self;
        }
    }
    if (self->refcount)
        (*self->refcount)++;
    if (self->flags & 1)
        func_0023B9C8(self);
    func_0023B3A8(self);
}
