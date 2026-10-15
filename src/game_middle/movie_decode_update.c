// SLY3_CFLAGS: -Os -G0
struct MovieDecodeState {
    unsigned char opaque00[0x10C];
    float first_frame_time;
    unsigned char *buffer;
    void *stream;
    unsigned char decoder_prefix[8];
    int picture_index;
    unsigned char opaque124[0x180 - 0x124];
    unsigned char output_queue[0xBC];
    int completion_semaphore;
    volatile int pending;
};
extern float D_0036BBD8;
int func_001DC430(void *state, int wait);
int func_002A9F68(void *decoder, void *picture, int stride);
void func_001DB6D8(void *state);
void func_001DB8C8(void *state);
int func_00293920(int value);
int func_002936C0(int semaphore);
void func_001DB490(void *queue);

void func_001DC2E8(struct MovieDecodeState *state)
{
    while (state->pending == 1)
        func_001DC430(state, 0);
    if (func_002A9F68((unsigned char *)state + 0x118, state->buffer + 0x285A80, 0x5CD) < 0)
        return;
    if (state->picture_index == 0) {
        state->first_frame_time = D_0036BBD8;
        func_001DB6D8(state);
        func_001DB8C8(state);
        func_00293920(0);
    }
    while (state->pending)
        func_001DC430(state, 0);
    func_002936C0(state->completion_semaphore);
    func_001DB490(state->output_queue);
}
