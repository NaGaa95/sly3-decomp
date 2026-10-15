// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "dmas.h"

extern "C" void CopyAb(void *pvDst, void *pvSrc, uint cb)
{
    if (((uint)pvDst | (uint)pvSrc | cb) & 3)
    {
        uchar *pbDst = (uchar *)pvDst;
        uchar *pbSrc = (uchar *)pvSrc;
        for (uint i = 0; i < cb; i++)
            *pbDst++ = *pbSrc++;
        return;
    }
    if (((uint)pvDst | (uint)pvSrc | cb) & 15)
    {
        uint *punDst = (uint *)pvDst;
        uint *punSrc = (uint *)pvSrc;
        int cun = cb >> 2;
        int cunOdd = cun & 3;
        int cunQuad = cun - cunOdd;
        int i;
        if (cunOdd)
        {
            for (i = cunOdd; i != 0; i--)
                *punDst++ = *punSrc++;
        }
        for (i = 0; i < cunQuad; i += 4)
        {
            uint n0 = punSrc[0];
            uint n1 = punSrc[1];
            uint n2 = punSrc[2];
            uint n3 = punSrc[3];
            punDst[0] = n0;
            punDst[1] = n1;
            punDst[2] = n2;
            punDst[3] = n3;
            punSrc += 4;
            punDst += 4;
        }
        return;
    }
    CopyAqw(pvDst, pvSrc, cb >> 4);
}
