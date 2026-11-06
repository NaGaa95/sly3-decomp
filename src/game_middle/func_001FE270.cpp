// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions -fno-rtti
// Load the object list of a spliced proxy source from a binary stream: reset the list, then for every entry read
// its header (kind byte, optional frame indices and tables, class id, object id), create the object for the two
// known classes (0xBF, 0xC0), let it load itself from the stream and append it; unknown entries are skipped.
#include "../P2/bis.h"
struct VTE { short delta, pad; void *fn; };
struct FrameObject { char pad[0xC]; VTE *vt; };
struct SpliceObject { char pad[0x18]; VTE *vt; };
struct FrameRef {
    // 8-byte reference holder (the pointer plus one unused word); it shares the stack slot of the allocation request.
    FrameObject *m_p;
    int m_pad;
    FrameRef(FrameObject *p);
    ~FrameRef()
    {
        if (m_p) {
            VTE *entry = &m_p->vt[2];
            ((void (*)(void *))entry->fn)((char *)m_p + entry->delta);
        }
    }
};
struct SpliceList {
    char pad00[0x40]; void *frame; char pad44[0xD0 - 0x44];
    int count; SpliceObject **objects; int mode; char padDC[0xE8 - 0xDC];
    void *table; char padEC[0xF4 - 0xEC]; void *table2;
};
struct SWALLOC { int cb; int cbAlign; };
extern "C" {
void func_0028FDE0(SpliceList *, CBinaryInputStream *);
void func_0011AF38(void *, int);
void func_0028C210(void *);
void func_0028C238(void *);
void *func_001D2538(SWALLOC *);
int func_00151C98(int, short *);
int func_00151D10(int, int *);
SpliceObject *func_001FD758(void *, SpliceList *, int);
SpliceObject *func_001FDE70(void *, SpliceList *, int);
void func_002BE8F8(FrameRef *, FrameObject *);
}
inline FrameRef::FrameRef(FrameObject *p) { func_002BE8F8(this, p); }
inline void *PvAllocSw(int cb, int cbAlign)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    SWALLOC *pswalloc = &swalloc;
    pswalloc->cbAlign = cbAlign;
    return func_001D2538(pswalloc);
}
extern "C" void func_001FE270(SpliceList *self, CBinaryInputStream *pbis)
{
    func_0028FDE0(self, pbis);
    switch (self->mode) {
    case 2:
        self->table2 = PvAllocSw(0xC, 0x10);
        func_0011AF38(self->table2, 0xF8);
        self->table = PvAllocSw(4, 0x10);
        break;
    case 0:
        func_0011AF38(&self->table, 0x80);
        break;
    }
    func_0028C210(self->frame);
    int count = pbis->S16Read();
    self->objects = (SpliceObject **)PvAllocSw(count * 4, 0x10);
    for (int i = 0; i < count; i++) {
        short aShort[0x80];
        int aInt[0x80];
        int kind = pbis->S8Read();
        int nShort, nInt;
        switch (kind) {
        case 0:
            nInt = 0;
            nShort = 0;
            break;
        case 1:
            nShort = pbis->U8Read();
            nInt = pbis->U8Read();
            pbis->Read(nShort * 2, aShort);
            pbis->Read(nInt * 4, aInt);
            break;
        }
        int cid = pbis->S16Read();
        int oid = pbis->S32Read();
        pbis->S16Read();
        int cb = pbis->S32Read();
        if (kind == 1 && (!func_00151C98(nShort, aShort) || !func_00151D10(nInt, aInt))) {
            pbis->Skip(cb);
            continue;
        }
        SpliceObject *obj;
        switch (cid) {
        case 0xBF:
            obj = func_001FD758(PvAllocSw(0x20, 0x10), self, oid);
            break;
        case 0xC0:
            obj = func_001FDE70(PvAllocSw(0x20, 0x10), self, oid);
            break;
        default:
            pbis->Skip(cb);
            continue;
        }
        {
            VTE *entry = &obj->vt[4];
            FrameRef ref(((FrameObject *(*)(void *))entry->fn)((char *)obj + entry->delta));
            VTE *load = &ref.m_p->vt[7];
            ((void (*)(void *, CBinaryInputStream *))load->fn)((char *)ref.m_p + load->delta, pbis);
            self->objects[self->count++] = obj;
        }
    }
    func_0028C238(self->frame);
}
