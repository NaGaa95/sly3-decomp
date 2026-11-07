// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00263748: LoadElemFromBrx - reads one sprite element from the stream (Sly 3 form of Sly 2 func_002149D8).
// Kinds: 4 index, 8 child list (each child is loaded recursively, into a throw-away heap when the save data does not
// have it; the kept ones are copied into an id table), 3 shader, 6/7 textured rectangle (GIF + VIF packet),
// 1 geometry records grouped into VU1 packets (microprogram 0x140). TMPHEAP is the scratch heap constructed by
// func_002BC528 and destroyed by func_002BC4D8 (one-argument constructor).
#include "../P2/gifs.h"
#include "../P2/vifs.h"
struct BIS;
struct SPRITE;
struct OWNER { char pad0[0xB4]; HEAP *heap; };
struct PAIR { short x, y; };
struct RAWCOLOR { uchar r, g, b, a; };
struct ENTRY { ushort id, pad2; float value; SPRITE *child; };
struct SPRITE { int pad0; int kind; OWNER *owner; int fC; int f10; int f14; float f18; float f1C; float f20; int f24; int f28; int f2C; };
struct SPRITE_GEOM { int pad0; int kind; OWNER *owner; int id; ushort count, groups; int samples; int packetCount; QW *packet; int f20; int f24; int pad[2]; };
struct RECORD { int kind, id; RAWCOLOR color; uchar count, padD[3]; int budget; uchar format, pad15[3]; PAIR *coordinates; uchar extra, pad1D[3]; uchar *extras; };
struct GROUP { int count, budget, samples; RECORD *begin, *end; };
struct CTX { CTX(); ~CTX(); };
struct TMPHEAP { char pad[0x10]; };
int U16Read(BIS *) asm("U16Read__18CBinaryInputStream");
int S32Read(BIS *) asm("S32Read__18CBinaryInputStream");
uint U32Read(BIS *) asm("U32Read__18CBinaryInputStream");
int U8Read(BIS *) asm("U8Read__18CBinaryInputStream");
int S8Read(BIS *) asm("S8Read__18CBinaryInputStream");
int S16Read(BIS *) asm("S16Read__18CBinaryInputStream");
float F32Read(BIS *) asm("F32Read__18CBinaryInputStream");
void *PvAllocStackClear(ALLOCREQ *) asm("func_001D2670");
extern "C" {
void func_00236970(void *);
int func_0014FEB0(void *, int);
void func_002BC528(TMPHEAP *);
void func_002BC4D8(TMPHEAP *, int);
void func_00263748(OWNER *, BIS *, SPRITE *, int);
}
extern char D_00475480[];
extern int D_0036B124;
extern QW D_003175A0;
extern char D_00000650[], D_00000140[];
static inline void *PvAllocStack(int cb) { ALLOCREQ request; request.cb = cb; request.cbAlign = 16; return PvAllocStackClear(&request); }
static inline void *Acquire(ALLOCREQ *request, int bytes, int alignment) { request->cb = bytes; request->cbAlign = alignment; return PvAllocStackClear(request); }
extern "C" void func_00263748(OWNER *owner, BIS *stream, SPRITE *sprite, int)
{
    CTX outer;
    sprite->owner = owner;
    sprite->kind = U32Read(stream);
    switch (sprite->kind) {
    case 0: case 2: case 5: default:
        break;
    case 4:
        sprite->fC = S32Read(stream);
        sprite->f10 = U16Read(stream);
        break;
    case 8: {
        int i;
        int count = 0;
        int mode = U8Read(stream);
        int n = U16Read(stream);
        ENTRY *entries = (ENTRY *)PvAllocStack(n * sizeof(ENTRY));
        for (i = 0; i < n; i++) {
            ENTRY *entry = &entries[i];
            entry->id = U16Read(stream);
            float value = F32Read(stream);
            entry->value = value;
            if (entry->id == 0x20)
                sprite->f18 = value;
            int fFound = func_0014FEB0(D_00475480, entry->id);
            int fUse = mode != 1 ? fFound : 1;
            if (mode == 2) {
                int fOk = 1;
                if (D_0036B124 < 7) {
                    if (D_0036B124 >= 5)
                        fOk = 0;
                }
                if (!fOk)
                    fUse = 0;
            }
            if (fUse) {
                count++;
                SPRITE *child = (SPRITE *)PvAllocClear(owner->heap, 0x30, 0x1D);
                entry->child = child;
                func_00263748(owner, stream, child, 1);
            } else {
                TMPHEAP heap;
                SPRITE dummy;
                HEAP *pheap = owner->heap;
                func_002BC528(&heap);
                owner->heap = (HEAP *)&heap;
                func_00263748(owner, stream, &dummy, 1);
                owner->heap = pheap;
                func_002BC4D8(&heap, 2);
            }
        }
        sprite->fC = count;
        sprite->f10 = (int)PvAllocClear(owner->heap, count * sizeof(ENTRY), 0x1D);
        sprite->f14 = (int)PvAllocClear(owner->heap, 0x400, 0x1D);
        ENTRY *dst = (ENTRY *)sprite->f10;
        for (int j = 0; j < n; j++) {
            ENTRY *entry = &entries[j];
            if (entry->child) {
                *dst = *entry;
                if (dst->id < 0x100)
                    ((ENTRY **)sprite->f14)[dst->id] = dst;
                dst++;
            }
        }
        ((ENTRY **)sprite->f14)[0xA0] = ((ENTRY **)sprite->f14)[0x20];
        break;
    }
    case 3:
        sprite->f14 = U32Read(stream);
        func_00236970(&sprite->f14);
        sprite->f18 = F32Read(stream);
        sprite->f20 = F32Read(stream);
        sprite->f1C = F32Read(stream);
        sprite->f24 = S8Read(stream);
        sprite->fC = S8Read(stream);
        sprite->f2C = S8Read(stream);
        if (sprite->fC == 1)
            sprite->f10 = S32Read(stream);
        else if (sprite->fC == 0)
            sprite->f10 = S32Read(stream);
        if (sprite->fC == 1) {
            if (sprite->f10 == 0x34F || sprite->f10 == 0x354)
                sprite->f28 = 1;
            else if (sprite->f10 == 0x3A0 || sprite->f10 == 0x3A1)
                sprite->f28 = 2;
            else
                sprite->f28 = 0;
        } else
            sprite->f28 = 0;
        break;
    case 6: case 7: {
        PAIR first, second;
        first.x = S16Read(stream); first.y = S16Read(stream); second.x = S16Read(stream); second.y = S16Read(stream);
        int texture = S32Read(stream);
        CTX inner;
        GIFS gif;
        gif.AllocSw(16);
        gif.AddPrimPack(0, 1, 0xE);
        switch (sprite->kind) {
        case 6:
            sprite->fC = texture;
            gif.PackAD(0x47, 0x5000F);
            gif.PackAD(0x42, 0x80000000A8L);
            break;
        case 7:
            sprite->fC = texture;
            gif.PackAD(0x42, 0x44);
            gif.PackAD(0x47, 0x50000);
            break;
        }
        gif.AddPrimPack(0x54, 9, 0x525252521L);
        gif.PackRGBA(0x80808080);
        switch (sprite->kind) {
        case 6:
            gif.PackSTQ(0.0f, 0.0f, 0.0f); gif.PackXYZ(first.x, first.y, 0);
            gif.PackSTQ(1.0f, 0.0f, 0.0f); gif.PackXYZ(second.x, first.y, 0);
            gif.PackSTQ(0.0f, 1.0f, 0.0f); gif.PackXYZ(first.x, second.y, 0);
            gif.PackSTQ(1.0f, 1.0f, 0.0f); gif.PackXYZ(second.x, second.y, 0);
            break;
        case 7:
            gif.PackSTQ(0.0f, 1.0f, 0.0f); gif.PackXYZ(first.x, first.y, 0);
            gif.PackSTQ(1.0f, 1.0f, 0.0f); gif.PackXYZ(second.x, first.y, 0);
            gif.PackSTQ(0.0f, 0.0f, 0.0f); gif.PackXYZ(first.x, second.y, 0);
            gif.PackSTQ(1.0f, 0.0f, 0.0f); gif.PackXYZ(second.x, second.y, 0);
            break;
        }
        gif.AddPrimPack(0, 1, 0xE);
        gif.PackAD(0x42, 0x44);
        gif.PackAD(0x47, 0x50000);
        gif.EndPrim(1);
        VIFS vif;
        vif.AllocSw(20);
        vif.AddDmaCnt();
        vif.AddVifUnpack(UPK_V4_32, ((uint)gif.m_pb - (uint)gif.m_ab) >> 4, gif.m_ab, 7);
        vif.AddVifMscal(D_00000650);
        vif.EndDmaCnt();
        vif.AddDmaRet();
        switch (sprite->kind) {
        case 6:
            vif.DetachCopySw(owner->heap, &sprite->f10, 0, (QW **)&sprite->f14);
            break;
        case 7:
            vif.DetachCopySw(owner->heap, &sprite->f10, 0, (QW **)&sprite->f14);
            break;
        }
        break;
    }
    case 1: {
        SPRITE_GEOM *geom = (SPRITE_GEOM *)sprite;
        geom->id = S32Read(stream);
        geom->count = U16Read(stream);
        geom->f24 = 0;
        RECORD *records;
        GROUP *groups;
        int i, j;
        {
            ALLOCREQ request;
            records = (RECORD *)Acquire(&request, geom->count * sizeof(RECORD), 16);
            groups = (GROUP *)Acquire(&request, geom->count * sizeof(GROUP), 16);
            for (i = 0; i < geom->count; i++) {
                RECORD *record = &records[i];
                record->count = U8Read(stream); record->format = U8Read(stream);
                record->kind = U8Read(stream); record->id = U8Read(stream); record->extra = U8Read(stream);
                record->budget = record->count + 2;
                record->coordinates = (PAIR *)Acquire(&request, record->count * sizeof(PAIR), 16);
                record->extras = (uchar *)Acquire(&request, record->count, 16);
                for (int k = 0; k < record->count; k++) {
                    PAIR *coordinate = &record->coordinates[k];
                    *(uint *)&record->color = U32Read(stream);
                    func_00236970(&record->color);
                    record->extras[k] = U8Read(stream);
                    coordinate->x = S16Read(stream); coordinate->y = S16Read(stream);
                }
            }
        }
        geom->groups = 0; geom->packetCount = 0; geom->samples = 0;
        for (i = 0; i < geom->count;) {
            GROUP *group = &groups[geom->groups];
            group->count = 0; group->samples = 0; group->budget = 0; group->begin = &records[i];
            while (i < geom->count && group->budget + records[i].budget < 0xBD) {
                group->budget += records[i].budget; group->samples += records[i].count; group->count++; i++; group->end = &records[i];
            }
            int estimate = (group->samples + 1) / 4 + group->samples / 16 + (group->count * 3 + 3) / 4 + 3;
            geom->packetCount += estimate;
            geom->samples += group->samples;
            geom->groups++;
        }
        VIFS vif; j = 0; vif.AllocSw(geom->packetCount * 2); vif.AddDmaCnt(); vif.AddVifStrow(&D_003175A0);
        for (; j < geom->groups; j++) {
            GROUP *group = &groups[j];
            int n = 0; QW header; header.an[0] = group->count; vif.AddVifUnpack(UPK_V2_32, 1, &header, 7); vif.AddVifStcycl(1, 2);
            uint *bytes, *colors;
            vif.UnpackHelper(UPK_V3_8, group->count, 8, 0, &bytes); vif.UnpackHelper(UPK_V4_8, group->count, 9, 0, &colors);
            int address = group->count * 2 + 8;
            vif.AddVifStcycl(1, 1);
            int base = address;
            vif.AddVifStmask(0x50505050);
            for (RECORD *record = group->begin; record != group->end; record++) {
                ((uchar *)bytes)[n * 3] = record->kind; ((uchar *)bytes)[n * 3 + 1] = record->count; ((uchar *)bytes)[n * 3 + 2] = record->format;
                *(RAWCOLOR *)&colors[n] = record->color; n++;
                vif.AddVifUnpack((UPK)(UPK_V2_16 + 16), record->count, record->coordinates, address); address += record->count;
            }
            vif.AddVifStmask(0x3F3F3F3F); address = base;
            for (RECORD *record = group->begin; record != group->end; record++) {
                if (record->extra) vif.AddVifUnpack((UPK)(UPK_S8 + 16), record->count, record->extras, address);
                address += record->count;
            }
            vif.AddVifStmask(0); vif.AddVifMscal(D_00000140);
        }
        vif.EndDmaCnt(); vif.AddDmaRet(); vif.DetachCopySw(owner->heap, &geom->packetCount, 0, &geom->packet);
        break;
    }
    }
}
