// SLY3_CFLAGS: -Os -G0 -ffast-math
// Bind a table of (flags, key, offset) entries into the fields of an object: depending on the flags the target is found
// in the source's record array (0x10), through func_0023F3B8 (0x20), func_0023F370 (0x40) or created by func_0017E1B8;
// 0x200 asks the target to run a follow-up (virtual slot 9 or the helper). This unit also holds two standalone helpers for the
// tagged flag word at +0x3C: func_001C8B58 sets bits, func_001C8B88 clears them (never clearing the pending bit 4 while the
// shared word has the lock bit 0x20). The tagged word is either a plain value (low bit set) or a pointer to the shared word.
struct VT { short d; short pad; void (*pfn)(void *); };
struct Handle { char pad00[0xC]; struct VT *vt; };
struct Record { char pad00[0x9C]; int key; char padA0[0x100 - 0xA0]; };
struct Source { char pad00[0x40]; int count; struct Record *records; };
struct Bind { int flags; int key; int offset; };
struct Owner { char pad[0x3C]; int flags; };
extern char D_00475480[];
struct Handle *func_0017E1B8(void *game, int kind, int key, struct Source *src);
void func_0023B978(struct Source *src, struct Handle *h);
int func_0023F370(struct Source *src, int key);
int func_0023F3B8(struct Source *src, int key);
void func_0023FEC0(struct Source *src, int key);
void func_001C8970(char *out, int count, struct Bind *binds, struct Source *source)
{
    struct Source *src = source ? source : (struct Source *)out;
    int i;
    for (i = 0; i < count; i++) {
        struct Bind *b = &binds[i];
        if (b->flags & 0x10) {
            int j = src->count;
            j--;
            while (j >= 0) {
                struct Record *r = (struct Record *)(j * sizeof(struct Record) + (int)src->records);
                j--;
                if (r->key == b->key) {
                    *(struct Record **)(out + b->offset) = r;
                    break;
                }
            }
        } else if (b->flags & 0x20) {
            int r = func_0023F3B8(src, b->key);
            if (r) {
                *(int *)(out + b->offset) = r;
                if (b->flags & 0x200)
                    func_0023B978(src, (struct Handle *)r);
            }
        } else if (b->flags & 0x40) {
            int r = func_0023F370(src, b->key);
            if (r) {
                *(int *)(out + b->offset) = r;
                if (b->flags & 0x200)
                    func_0023FEC0(src, b->key);
            }
        } else {
            int kind;
            struct Handle *h;
            if (b->flags & 2)
                kind = 4;
            else
                kind = (b->flags & 1) ? 5 : 1;
            h = func_0017E1B8(D_00475480, (b->flags & 0x400) ? (kind | 0x400) : kind, b->key, src);
            if (h) {
                if (b->flags & 0x200)
                    h->vt[9].pfn((char *)h + h->vt[9].d);
                *(struct Handle **)(out + b->offset) = h;
            }
        }
    }
}
void func_001C8B58(struct Owner *owner, int bits)
{
    int tagged = owner->flags;
    if ((tagged ^ 1) & 1)
        *(int *)tagged |= bits;
    else
        owner->flags = tagged | bits;
}
static inline unsigned int GetFlags(struct Owner *owner)
{
    unsigned int tagged = owner->flags;
    return ((tagged ^ 1) & 1) ? *(unsigned int *)tagged : tagged;
}
void func_001C8B88(struct Owner *owner, int bits)
{
    int tagged;
    if (bits & 4) {
        if (GetFlags(owner) & 0x20)
            bits &= ~4;
    }
    tagged = owner->flags;
    if ((tagged ^ 1) & 1)
        *(int *)tagged &= ~bits;
    else
        owner->flags = tagged & ~bits;
}
