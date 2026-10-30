// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Load one group's records from its compressed "SLD." stream (stream/key code shaped like func_00260A60).
struct ALLOCREQ { int cb; int cbAlign; ALLOCREQ(int b, int a) { cb = b; cbAlign = a; } };
class CTX {
    int storage[4];
public:
    CTX() __asm__("__3CTX");
    ~CTX() __asm__("_$_3CTX");
};
struct Stream { unsigned char storage[0x70]; };
struct Key {
    unsigned int low; unsigned int high; int mode; unsigned char flags;
    void SetMode(int m) { mode = m; }
};
struct VTE { short d; short pad; void (*pfn)(void *, int, Stream *, void *); };
struct LOADER { unsigned char pad[0xC]; struct VTE *vt; };
struct ENT { int kind; struct LOADER *obj; int arg; };
struct GRP { unsigned int w0; unsigned int w4; unsigned char pad8[0x34 - 8]; unsigned int w34; unsigned char pad38[4]; unsigned int w3C; int id; int iEnd; };
struct WLD { unsigned char pad[0x40]; int cgrp; struct GRP *agrp; unsigned char pad48[4]; struct ENT *aent; unsigned char x50[0x14];
    unsigned char x64[0x698 - 0x64]; int igrp; };
extern "C" {
int func_0016F5E8(struct WLD *w);
void func_0016F120(struct WLD *w);
void func_00196AF8(void *p);
void *PvAllocSlot(ALLOCREQ *req) __asm__("PvAllocSlot__FP8ALLOCREQ");
void func_001A2C88(Stream *s, int cb, void *pv, int grf);
void func_001A2D30(Stream *s, int flags);
void func_002BC568(Key *key);
int func_001A3118(Stream *s, Key *key);
void SetDecompress(Stream *s, int n, void *pb) __asm__("SetDecompress__18CBinaryInputStreamiPUc");
unsigned char U8Read(Stream *s) __asm__("func_00118FF8");
unsigned short U16Read(Stream *s) __asm__("U16Read__18CBinaryInputStream");
int strncmp(const char *a, const char *b, unsigned int n);
void func_00236AE0(void);
void func_0025C930(int n, Stream *s);
void func_00234EA0(void *p, int n, Stream *s, void *q);
void func_00235DE0(void);
void func_00236B80(void);
}
extern "C" void func_0016F2B0(struct WLD *w, int id)
{
    int i;
    struct GRP *grp;
    int j;

    if (id == func_0016F5E8(w))
        return;
    for (i = 0; i < w->cgrp; i++) {
        if (w->agrp[i].id == id)
            break;
    }
    if (i >= w->cgrp)
        return;
    grp = &w->agrp[i];
    func_0016F120(w);
    func_00196AF8(w->x64);
    CTX ctx;
    void *buffer;
    {
        ALLOCREQ request(0x10000, 0x40);
        buffer = PvAllocSlot(&request);
    }
    Stream storage;
    Stream *stream = &storage;
    func_001A2C88(stream, 0x10000, buffer, 0);
    Key key;
    char name[0x100];
    int ok;
    key.SetMode(2);
    func_002BC568(&key);
    if (!grp)
        ok = 0;
    else {
        unsigned int high = grp->w4 ^ grp->w3C;
        unsigned int low = (grp->w0 ^ grp->w34) + 0xCA0;
        key.SetMode(2);
        key.low = low;
        key.high = high;
        ok = high != 0;
    }
    if (!ok || !func_001A3118(stream, &key))
        goto fail;
    {
        ALLOCREQ request(0x4000, 0x40);
        SetDecompress(stream, 0x4000, PvAllocSlot(&request));
    }
    {
    char magic[4];
    int version;
    magic[0] = U8Read(stream);
    magic[1] = U8Read(stream);
    magic[2] = U8Read(stream);
    magic[3] = U8Read(stream);
    version = U16Read(stream);
    if (strncmp(magic, "SLD.", 4) || version != 1) {
    fail:
        func_001A2D30(stream, 2);
        return;
    }
    }
    func_00236AE0();
    func_0025C930(1, stream);
    func_00234EA0(w->x64, 0, stream, w->x50);
    for (j = i > 0 ? w->agrp[i - 1].iEnd : 0; j < grp->iEnd; j++) {
        struct ENT *e = &w->aent[j];
        switch (e->kind) {
        case 0:
            if (e->obj)
                e->obj->vt[15].pfn((char *)e->obj + e->obj->vt[15].d, -1, &storage, w);
            break;
        case 1:
            if (e->obj)
                e->obj->vt[15].pfn((char *)e->obj + e->obj->vt[15].d, e->arg, &storage, w);
            break;
        }
    }
    func_00235DE0();
    func_00236B80();
    w->igrp = i;
    func_001A2D30(&storage, 2);
}
