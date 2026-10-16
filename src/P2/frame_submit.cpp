// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct S;
struct sceDmaChan;
union QW;
struct FrameSubmitView {
    int unknown0;
    QW *gifsPacket;
    char unknown8[0x24-8];
    QW *mainPacket;
    char unknown28[0x30-0x28];
    int flags;
    char unknown34[0x60-0x34];
    char primaryPrelude[0xA0];
    char secondaryPrelude[0x90];
};
struct FrameSubmitScreen {
    int mode, width, height, flags;
};
struct FrameSubmitGame {
    char unknown[0x3EB8];
    int count;
    void *providers[5];
};
extern "C" {
extern char D_0036DBE0[], D_0036E3D0[], D_0036E470[], D_0036E500[], D_0036E5A0[];
extern sceDmaChan *D_0036BD3C, *D_0036BD40;
extern FrameSubmitGame D_00475480;
void func_00238060(S *frame);
void func_00196050(int screenArg0, int screenArg1);
void func_001D2820(void *destination, void *source, int qwordCount);
void func_00293920(int operation);
void func_00195760(sceDmaChan *channel, QW *packet);
void func_00167DD8(void *object, FrameSubmitView *frame);
}
extern "C" void func_00183370(FrameSubmitView *frame, int screenArg0, int screenArg1, int sendGIFS)
{
    func_00238060(reinterpret_cast<S *>(frame));
    func_00196050(screenArg0, screenArg1);
    if (((reinterpret_cast<FrameSubmitScreen *>(D_0036DBE0)->flags>>1)&1) &&
       (frame->flags&8)) {
        func_001D2820(frame->primaryPrelude, D_0036E3D0, 10);
        func_001D2820(frame->secondaryPrelude, D_0036E470, 9);
    }
    func_00293920(0);
    func_00195760(D_0036BD3C, frame->mainPacket);
    if (((reinterpret_cast<FrameSubmitScreen *>(D_0036DBE0)->flags>>1)&1) &&
       (frame->flags&8)) {
        func_001D2820(frame->primaryPrelude, D_0036E500, 10);
        func_001D2820(frame->secondaryPrelude, D_0036E5A0, 9);
        for (int i=0; i<D_00475480.count; ++i)
            func_00167DD8(D_00475480.providers[i], frame);
        func_00293920(0);
        func_00195760(D_0036BD3C, frame->mainPacket);
    }
    if (sendGIFS)
        func_00195760(D_0036BD40, frame->gifsPacket);
}
