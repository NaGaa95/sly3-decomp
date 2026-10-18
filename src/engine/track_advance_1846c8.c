// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct TrackCursor {
    unsigned char prefix[0x40];
    void *track40;
    unsigned char opaque44[0x2C];
    float progress70;
};
void func_0022EA88(void *track, Qword position, void *first, Qword *second, Qword *third, float *fourth, float *progress);
float func_0022DFD8(void *track);
void func_00184728(struct TrackCursor *cursor);
void func_001846C8(struct TrackCursor *cursor, Qword position)
{
    func_0022EA88(cursor->track40, position, 0, 0, 0, 0, &cursor->progress70);
    if(cursor->progress70 < func_0022DFD8(cursor->track40)) func_00184728(cursor);
}
