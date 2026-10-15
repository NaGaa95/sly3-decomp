// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"
struct CompactTimeSequence {
    signed char wide;
    unsigned char count;
    unsigned char bytes[0];
};
extern "C" void func_0012D078(CompactTimeSequence *sequence,CBinaryInputStream *stream)
{
    sequence->wide=stream->S8Read();
    sequence->count=stream->U8Read();
    if(sequence->wide==0)
        stream->Read(sequence->count,sequence->bytes);
    else
        stream->Read(sequence->count*2,sequence->bytes);
}
extern "C" int func_0012D0F0(CompactTimeSequence *sequence,float time)
{
    int frame=(int)(time*60.0f);
    int index=1;
    if(sequence->wide==0) {
        for(;index<sequence->count-1;++index)
            if(frame<sequence->bytes[index])break;
    } else {
        const unsigned short *times=(const unsigned short *)sequence->bytes;
        for(;index<sequence->count-1;++index)
            if(frame<times[index])break;
    }
    return index;
}
