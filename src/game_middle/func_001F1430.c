// Select the display-list buffer layout for a render mode (3: full, 2: reduced, otherwise none) and rebind the
// two frame records' GIF/VIF buffers and ring. Reference algorithm: Sly 2 func_001C2A78.
// SLY3_CFLAGS: -Os -G0
struct FrameBuffers {
    int pad0[2];
    char *gifBuf;
    int gifBufSize;
    int pad10[2];
    char *vifBuf;
    int vifBufSize;
    int pad20[12];
    char *ringStart;
    char *ringCursor;
    char *ringEnd;
    int pad5C[0x190 / 4 - 0x5C / 4];
};
extern struct FrameBuffers D_0036C330[2];
extern char D_0038AF00[];
extern char D_00396F00[];
extern char D_00446F00[];
extern char D_00462B00[];
extern int D_00467B00;
void func_00293920(int n);
void func_001F1430(int mode)
{
    struct FrameBuffers *pb;
    char *ring;
    int i;
    if (mode == D_00467B00)
        return;
    func_00293920(0);
    D_00467B00 = mode;
    switch (mode) {
    case 3:
        for (i = 0; i < 2; i++) {
            pb = &D_0036C330[i];
            ring = D_00446F00 + i * 0x600;
            pb->gifBuf = D_0038AF00 + i * 0x6000;
            pb->vifBufSize = 0x5800;
            pb->vifBuf = D_00396F00 + i * 0x58000;
            pb->gifBufSize = 0x600;
            pb->ringCursor = ring;
            pb->ringStart = ring;
            pb->ringEnd = ring + 0x600;
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            pb = &D_0036C330[i];
            pb->gifBuf = D_00462B00 + i * 0x2000;
            pb->gifBufSize = 0x200;
            pb->vifBufSize = 0x80;
            pb->vifBuf = D_00462B00 + 0x4000 + i * 0x800;
            pb->ringCursor = 0;
            pb->ringStart = 0;
            pb->ringEnd = 0;
        }
        break;
    default:
        for (i = 0; i < 2; i++) {
            pb = &D_0036C330[i];
            pb->gifBufSize = 0;
            pb->gifBuf = 0;
            pb->vifBufSize = 0;
            pb->vifBuf = 0;
            pb->ringCursor = 0;
            pb->ringStart = 0;
            pb->ringEnd = 0;
        }
        break;
    }
}
