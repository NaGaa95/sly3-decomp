// SLY3_CFLAGS: -Os -G0
struct MovieStopState {
    unsigned char opaque00[0x10C];
    float first_frame_time;
    void *buffer;
    void *stream;
    unsigned char opaque118[0x180 - 0x118];
    unsigned char output_queue[0xBC];
    int completion_semaphore;
    volatile int pending;
};
void func_001DB308(void *queue);
void func_001DB368(void *queue);
int func_002A9FB8(void *decoder);
int func_002A9F58(void *decoder);

void func_001DC3B8(struct MovieStopState *state)
{
    state->stream = 0;
    state->first_frame_time = 0.0f;
    func_001DB308(state->output_queue);
    func_001DB368(state->output_queue);
    func_002A9FB8((unsigned char *)state + 0x118);
    func_002A9F58((unsigned char *)state + 0x118);
    while (state->pending) {}
}
