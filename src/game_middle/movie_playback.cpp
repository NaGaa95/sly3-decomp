// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "heap_frame_api.h"
#include "../P2/heap.h"

class MoviePlaybackFrame {
public:
    MoviePlaybackFrame() __asm__("func_001D2770");
    ~MoviePlaybackFrame() { func_001D2798(this, 2); }
};

extern "C" void func_0013AFA8(void *stream, int flags);
class MoviePlaybackStream {
    unsigned char storage[0x30];
public:
    MoviePlaybackStream(int capacity, int buffer_address) __asm__("func_0013AF60");
    ~MoviePlaybackStream() { func_0013AFA8(this, 2); }
};

struct MoviePlaybackRecord {
    unsigned int word0, word4, word8;
    unsigned char opaque0C[0x34 - 12];
    unsigned int word34, word38, word3C;
};
extern "C" void func_002BC568(void *input);
struct MoviePlaybackInput {
    unsigned int first, second;
    int type;
    unsigned char byte0C;
    unsigned char opaque0D[0x110 - 13];

    MoviePlaybackInput() {
        type = 2;
        func_002BC568(this);
    }
    bool Set(const MoviePlaybackRecord *record) {
        if (!record)
            return false;
        unsigned int start = record->word0 ^ record->word34;
        unsigned int bytes = record->word4 ^ record->word3C;
        type = 2;
        first = start + 0xCA0;
        second = bytes;
        return bytes != 0;
    }
};
struct MoviePlaybackState {
    unsigned char opaque00[0x108];
    int repeat;
    float first_frame_time;
    unsigned char *buffer;
};
struct MoviePlaybackSave {
    unsigned char opaque00[0x13950];
    void *selected;
};

typedef char MoviePlaybackFrameSize[(sizeof(MoviePlaybackFrame) == 1) ? 1 : -1];
typedef char MoviePlaybackStreamSize[(sizeof(MoviePlaybackStream) == 48) ? 1 : -1];
typedef char MoviePlaybackInputSize[(sizeof(MoviePlaybackInput) == 272) ? 1 : -1];
typedef char MoviePlaybackRecordSize[(sizeof(MoviePlaybackRecord) == 64) ? 1 : -1];

extern "C" {
extern MoviePlaybackRecord D_00317F38, D_00317F78;
extern int D_00389D08, D_00345FD0, D_003440C0;
extern unsigned char D_0036BB98[], D_00375290[];
void *func_001D2670(ALLOCREQ *request);
int func_0013AFF0(void *stream, void *input);
void func_001DC158(void *state, int stream_address);
int func_002AA038(void *decoder);
void func_00165430(void *clock, int paused);
void func_001A77A0(void);
void func_001CF0D0(void *save);
unsigned int func_001A7980(int mask);
void func_00162E80(void);
void func_001DC2E8(void *state);
void func_001DC3B8(void *state);
void func_0013B078(void *stream);
}

static inline int SameMovie(const MoviePlaybackRecord *a,
                            const MoviePlaybackRecord *b)
{
    if (a == b)
        return 1;
    if (!a || !b)
        return 0;
    return ((a->word8 ^ a->word38) ^ (b->word8 ^ b->word38)) == 0;
}

static inline ALLOCREQ *SetMovieRequest(ALLOCREQ *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->cbAlign = alignment;
    return request;
}

extern "C" void func_001DBE80(MoviePlaybackState *state,
                              const MoviePlaybackRecord *record)
{
    MoviePlaybackFrame frame;
    ALLOCREQ request;
    state->buffer = (unsigned char *)func_001D2670(SetMovieRequest(&request, 0x41FC00, 0x40));
    MoviePlaybackStream stream(0x80000, (int)state->buffer);
    MoviePlaybackInput input;

    if (input.Set(record) && func_0013AFF0(&stream, &input)) {
        func_001DC158(state, (int)&stream);
        while (!func_002AA038((unsigned char *)state + 0x118)) {
            func_00165430(D_0036BB98, 1);
            func_001A77A0();
            MoviePlaybackSave *save = (MoviePlaybackSave *)D_00375290;
            if (!save->selected)
                func_001CF0D0(save);
            int skip = 0;
            if (SameMovie(record, &D_00317F38) || SameMovie(record, &D_00317F78))
                skip = D_00389D08 != 0;
            if (D_00345FD0)
                skip = 1;
            if (skip && func_001A7980(0x91F)) {
                state->repeat = 0;
                break;
            }
            if (input.type == 2) {
                func_00162E80();
                if (D_003440C0 != 3)
                    break;
            }
            func_001DC2E8(state);
        }
        if (SameMovie(record, &D_00317F78))
            D_00389D08 = 1;
        func_001DC3B8(state);
        func_0013B078(&stream);
    }
    state->buffer = 0;
}
