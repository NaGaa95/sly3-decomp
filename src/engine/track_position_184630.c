// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct TrackCursor {
    unsigned char prefix[0x40];
    void *track40;
    void *scene44;
    unsigned char opaque48[0x28];
    float progress70;
};
void func_0022E330(void *track, Qword *output, void *second, float parameter);
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void func_001DC7E0(int *count, void ***records);
void func_00184580(struct TrackCursor *cursor, Qword *position, Qword *second, int count, void **records, float upper, float lower);
Qword func_00184630(struct TrackCursor *cursor)
{
    Qword position;
    void *frame;
    int count;
    void **records;
    func_0022E330(cursor->track40, &position, 0, cursor->progress70);
    if(cursor->scene44) {
        func_001D2770(&frame);
        func_001DC7E0(&count, &records);
        func_00184580(cursor, &position, 0, count, records, 100.0f, -350.0f);
        func_001D2798(&frame, 2);
    }
    return position;
}
