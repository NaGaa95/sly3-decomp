// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
typedef struct CRef {
    short tag, word2;
    float payload;
} CRef;
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern float D_0036BB9C;
CRef *func_00125A10(CRef *output, int count, CRef *arguments, struct CFrame *frame)
{
    output->tag = 0x14;
    output->payload = D_0036BB9C;
    return output;
}
