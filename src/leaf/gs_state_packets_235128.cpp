// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// func_00235128: after the resource batch is loaded, build the fixed GIF state packets of every 44-byte draw entry
// (D_0046FF3C, D_0046FF38 entries). Each entry owns one or two pre-allocated packet buffers (count + data); the entry kind
// selects the register sequence: kinds 0/4/5/6 textured draw state, 1 two-pass textured state, 2 fixed pair of alpha/test
// writes, 3 four-packet colour state (combine/fog/alpha sequence), 7 optional pre-pass plus the two passes of kind 1.
// Ported from the Sly 2 builder (func_001EB960); the Sly 3 kind 0 test word is the arithmetic ZTE/ATST/AREF word below.
#include "../P2/gifs.h"

struct RGBA { uchar r, g, b, a; };
struct PACKET { int count; QW *data; };
struct TEXTURE;
struct ENTRY {
    char unknown0[4];
    uchar kind, flags;
    char unknown6[6];
    RGBA color, secondary;
    char unknown14[4];
    TEXTURE *texture;
    int unknown1C;
    PACKET *packets;
    char unknown24[8];
};

extern int D_0046FF38;
extern ENTRY *D_0046FF3C;
extern uint D_0036BC30;

extern "C" void func_00233D58(TEXTURE *, int, GIFS *);
extern "C" void func_00235128();

static inline ulong ColorWord(const RGBA &color, const ENTRY *entry)
{
    ulong value = (ulong)color.r | ((ulong)color.g << 8) | ((ulong)color.b << 16);
    if (entry->flags & 2)
        return (value | ((ulong)color.a << 24)) | (1UL << 32);
    return value | (1UL << 32);
}

static inline void Pair(GIFS &q, int first, ulong regs)
{
    q.AddPrimBulk(first, 0, 4, regs, 0);
    q.AddPrimBulk(first + 1, 0, 4, regs, 0);
}

static inline void Packed(GIFS &q) { q.AddPrimPack(0, 1, 0xE); }

static inline void End(GIFS &q)
{
    q.GIFS::EndPrim(1);
    q.EndDmaCnt();
}

union BLEND_WORD {
    ulong value;
    struct {
        ulong first : 2;
        ulong second : 2;
        ulong third : 2;
        ulong fourth : 2;
        ulong remaining : 56;
    } fields;
};

static inline ulong Alpha(ENTRY *e)
{
    BLEND_WORD word;
    word.value = 0;
    word.fields.second = (e->flags & 1) ? 2UL : 1UL;
    word.fields.fourth = 1;
    return word.value;
}

void func_00235128()
{
    int i;
    for (i = 0; i < D_0046FF38; i++) {
        ENTRY *e = D_0046FF3C + i;
        PACKET *p = e->packets;
        switch (e->kind) {
        case 0: case 4: case 5: case 6: {
            GIFS q;
            q.AllocStatic(p->count, p->data);
            Pair(q, 0x7C, 0x4F12);
            Packed(q);
            func_00233D58(e->texture, 0, &q);
            ulong ate = !(e->flags & 0x20);
            q.PackAD(0x47, ((e->kind == 0) ? (ate | 0x117EAUL) : (ate | 0x117E0UL)) | (e->kind ? 0x20000UL : 0x60000UL));
            q.PackAD(0x42, Alpha(e));
            q.PackAD(0x3D, (ulong)D_0036BC30);
            End(q);
            break;
        }
        case 3: {
            GIFS q;
            RGBA rounded, color;
            q.AllocStatic(p->count, p->data);
            if (e->flags & 2) {
                Pair(q, 0x7C, 0x4F12);
                Packed(q);
                func_00233D58(e->texture, 0, &q);
                q.PackAD(0x47, 0x71001);
                q.PackAD(0x42, Alpha(e));
                q.PackAD(0x3D, (ulong)D_0036BC30);
            } else {
                Pair(q, 0x4C, 0x4FFF);
                Packed(q);
                q.PackAD(0x47, 0x71001);
                q.PackAD(0x42, 0x6A);
                q.PackAD(1, (1UL << 32) | 0x20);
            }
            End(q);
            ++p;
            int one = 1;
            int two = 2;
            ulong mask = 0x40;
            q.Clear();
            q.AllocStatic(p->count, p->data);
            ++p;
            Pair(q, 0x4C, 0x4FFF);
            Packed(q);
            q.PackAD(0x47, 0x71001);
            q.PackAD(0x42, 0x6A);
            q.PackAD(1, (1UL << 32) | 0x80002000UL);
            End(q);
            q.Clear();
            q.AllocStatic(p->count, p->data);
            ++p;
            Pair(q, 0x6C, 0x4FFF);
            q.AddPrimPack(0, 5, 0x12EEE);
            q.PackAD(0x47, 0x75001);
            {
                ulong blendSource = 1;
                if (e->flags & 1)
                    blendSource = two;
                q.PackAD(0x42, (blendSource << 2) | mask);
            }
            q.PackAD(0x3D, (ulong)D_0036BC30);
            q.PackSTQ(0.f, 0.f, 1.f);
            {
                rounded.r = (e->color.r + 1) >> 1;
                rounded.g = (e->color.g + 1) >> 1;
                rounded.b = (e->color.b + 1) >> 1;
                rounded.a = (e->color.a + 1) >> 1;
                q.PackRGBA(*(uint *)&rounded);
            }
            End(q);
            q.Clear();
            q.AllocStatic(p->count, p->data);
            q.AddPrimBulk(0x4D, 0, 1, 4, 0);
            {
                color = e->secondary;
                Packed(q);
                if (e->flags & 1)
                    one = two;
                q.PackAD(0x42, (one << 2) | mask);
                q.PackAD(1, ColorWord(color, e));
            }
            End(q);
            break;
        }
        case 2: {
            GIFS q;
            q.AllocStatic(p->count, p->data);
            q.AddGifTag(0x44, 0, 2, 0x41, 1);
            q.AddGifTag(0x45, 0, 2, 0x41, 1);
            Packed(q);
            if (e->flags & 4)
                q.PackAD(0x47, 0x71001);
            else
                q.PackAD(0x47, 0x75001);
            q.PackAD(0x42, (1UL << 39) | 0x62);
            ++p;
            End(q);
            q.Clear();
            q.AllocStatic(p->count, p->data);
            q.AddGifTag(0x44, 0, 2, 0x41, 1);
            q.AddGifTag(0x45, 0, 2, 0x41, 1);
            Packed(q);
            if (e->flags & 4)
                q.PackAD(0x47, 0x31001);
            else
                q.PackAD(0x47, 0x35001);
            q.PackAD(0x42, (1UL << 39) | 0x68);
            End(q);
            break;
        }
        case 1: {
            GIFS q;
            q.AllocStatic(p->count, p->data);
            ++p;
            Pair(q, 0x7C, 0x4F12);
            Packed(q);
            func_00233D58(e->texture, 1, &q);
            q.PackAD(0x47, !(e->flags & 0x20) ? 0x717EBUL : 0x717EAUL);
            q.PackAD(0x42, Alpha(e));
            q.PackAD(0x3D, (ulong)D_0036BC30);
            End(q);
            q.Clear();
            q.AllocStatic(p->count, p->data);
            Pair(q, 0x7C, 0x41F2);
            Packed(q);
            func_00233D58(e->texture, 0, &q);
            q.PackAD(0x47, 0x51001);
            q.PackAD(0x42, 0x48);
            q.PackAD(0x3D, 0);
            End(q);
            break;
        }
        case 7: {
            GIFS q;
            if (!(e->flags & 0x10)) {
                q.AllocStatic(p->count, p->data);
                ++p;
                Pair(q, 0x7C, 0x41F2);
                Packed(q);
                func_00233D58(e->texture, 2, &q);
                q.PackAD(0x47, 0x5000D);
                q.PackAD(0x42, 0x40);
                q.PackAD(0x3D, 0);
                End(q);
                q.Clear();
            }
            q.AllocStatic(p->count, p->data);
            ++p;
            Pair(q, 0x7C, 0x4F12);
            Packed(q);
            func_00233D58(e->texture, 1, &q);
            q.PackAD(0x47, 0x53001);
            q.PackAD(0x42, Alpha(e));
            q.PackAD(0x3D, (ulong)D_0036BC30);
            End(q);
            q.Clear();
            q.AllocStatic(p->count, p->data);
            Pair(q, 0x7C, 0x41F2);
            Packed(q);
            func_00233D58(e->texture, 0, &q);
            q.PackAD(0x47, 0x53001);
            q.PackAD(0x42, 0x48);
            q.PackAD(0x3D, 0);
            End(q);
            break;
        }
        }
    }
}
