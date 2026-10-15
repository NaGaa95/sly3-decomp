// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
typedef struct CRef {
    short tag, word2;
    int payload;
} CRef;
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
CRef *func_001258F8(CRef *output, int count, CRef *arguments, struct CFrame *frame)
{
    int remainder = arguments[0].payload % arguments[1].payload;
    output->tag = 0x13;
    output->payload = remainder;
    return output;
}
