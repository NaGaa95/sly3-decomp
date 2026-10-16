// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct OutputFlushAccess {
    char *memory;
    int capacity,memoryCount,fd,total,bufferCapacity,bufferCount;
    char *buffer;
};
extern "C" {
void func_001D2898(void *destination,void *source,unsigned int bytes);
int func_002955E0(const char *format,...);
int func_002971A8(int fd,const void *buffer,int bytes);
extern char D_00327530[];
void func_0025A400(OutputFlushAccess *stream)
{
    if (stream->bufferCount==0 || stream->memory) return;
    if (stream->fd<0) {
        char *position=stream->buffer;
        int offset;
        for (offset=0;offset<stream->bufferCount;) {
            char text[0x88];
            int remaining=stream->bufferCount-offset;
            int bytes=0x80;
            if (remaining<0x80) bytes=remaining;
            func_001D2898(text,position,bytes);
            offset+=bytes;
            position+=bytes;
            text[bytes]=0;
            func_002955E0(D_00327530,text);
        }
    } else {
        func_002971A8(stream->fd,stream->buffer,stream->bufferCount);
    }
    stream->bufferCount=0;
}
}
