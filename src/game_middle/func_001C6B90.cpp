// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions -fno-rtti
// Write one VIF UNPACK packet (tag + 12 words of the entry's block) per entry into the VIFS stream, then pad the list to four
// packets with the default block; the result records the start of the stream and its length in quadwords.
#include "../P2/vifs.h"
struct Block { int w[12]; };
static inline void CopyQws(uint *pwDst, const uint *pwSrc, int cw)
{
    // empty do-while(0) (as left by a statement macro): its loop notes keep the loop setup below the tag/pb stores
    do
    {
    } while (0);
    for (int k = 0; k < cw; k += 4)
    {
        uint w0 = pwSrc[0];
        uint w1 = pwSrc[1];
        uint w2 = pwSrc[2];
        uint w3 = pwSrc[3];
        pwSrc += 4;
        pwDst[0] = w0;
        pwDst[1] = w1;
        pwDst[2] = w2;
        pwDst[3] = w3;
        pwDst += 4;
    }
}
struct Result { char pad[0x14]; int qwc; uchar *start; };
struct Entry { char pad[0x110]; Block block; };
static inline void AddUnpack(DMAS *dmas, int tag, Block *src)
{
    *(uint *)dmas->m_pb = tag | 0x6C03C000;
    dmas->m_pb += 4;
    CopyQws((uint *)dmas->m_pb, (const uint *)src, 12);
    dmas->m_pb += 12 * 4;
}
extern "C" {
extern VIFS D_0036C308;
extern Block D_003457F0;
void func_001C5868(Entry *e);
void func_001C6B90(int unused, int count, Entry **entries, Result *result)
{
    int i = 0;
    result->start = D_0036C308.m_pb;
    if (count > 0) {
        Entry **p = entries;
        int tag = 0x17;
        for (i = count; i != 0; i--) {
            Entry *e = *p;
            func_001C5868(e);
            AddUnpack(&D_0036C308, tag, &e->block);
            tag += 3;
            p++;
        }
        i = count;
    }
    if (i < 4) {
        int tag = i * 3 + 0x17;
        do {
            AddUnpack(&D_0036C308, tag, &D_003457F0);
            i++;
            tag += 3;
        } while (i < 4);
    }
    result->qwc = (int)(D_0036C308.m_pb - result->start) >> 4;
}
}
