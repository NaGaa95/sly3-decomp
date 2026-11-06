// SLY3_CFLAGS: -Os -G0 -fno-sched-interblock
// Movie render thread: each pass waits on the render semaphore, then submits the front packet, the optional
// overlay packet and the back packet twice (phase 0..2, then the second field).
struct MovieRenderState {
    unsigned char opaque00[0x104];
    void *stream;
    unsigned char opaque108[4];
    float time;
    unsigned char *packet_buffer;
    unsigned char opaque114[0x23C - 0x114];
    int semaphore;
    volatile int phase;
};
extern struct MovieRenderState D_00389AC0;
extern int D_0036BD40, D_0036DC98;
extern float D_0036BBD8;
void func_002936E0(int semaphore);
void func_00195760(int channel, void *packet);
void func_00196050(int index, int mode);
void func_00293920(int mode);
int func_0011EE30(void *stream, float time);
void func_001956B8(void);

void func_001DAA08(void *unused_start_argument)
{
    for (;;) {
        unsigned char *overlay;
        D_00389AC0.phase = 0;
        func_002936E0(D_00389AC0.semaphore);
        D_00389AC0.phase = 1;
        func_00195760(D_0036BD40, D_00389AC0.packet_buffer + 0x3F8E80);
        D_00389AC0.phase = 2;
        D_0036DC98 = 0;
        func_00196050(0, 0);
        func_00293920(0);
        if (D_00389AC0.stream && func_0011EE30((char *)D_00389AC0.stream + 8, D_0036BBD8 - D_00389AC0.time))
            overlay = D_00389AC0.packet_buffer + 0x41DC00;
        else
            overlay = 0;
        func_00195760(D_0036BD40, D_00389AC0.packet_buffer + 0x41BC00);
        if (overlay)
            func_00195760(D_0036BD40, overlay);
        func_001956B8();
        D_0036DC98 = 1;
        func_00196050(1, 0);
        func_00293920(0);
        func_00195760(D_0036BD40, D_00389AC0.packet_buffer + 0x41BC00);
        if (overlay)
            func_00195760(D_0036BD40, overlay);
        func_001956B8();
    }
}
