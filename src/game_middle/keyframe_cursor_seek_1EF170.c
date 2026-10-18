// SLY3_CFLAGS: -Os -G0 -fno-strength-reduce
typedef int qword __attribute__((mode(TI)));
struct KeyCursor {
    int index;
    float low;
    float high;
    unsigned char gapC[4];
    qword valueA;
    qword valueB;
    int count;
    unsigned char gap34[0x40 - 0x34];
    qword valuesA[16];
    qword valuesB[16];
    float times[1];
};
int func_001EF170(struct KeyCursor *cursor, float time)
{
    int index;
    if (time < cursor->low || cursor->high <= time) {
        if (cursor->times[cursor->index] < time) {
            int last = cursor->count - 1;
            index = cursor->index;
            while (index < last && !(time < cursor->times[index]))
                index++;
            index--;
        } else {
            index = cursor->index;
            while (index > 0 && !(cursor->times[index] <= time))
                index--;
        }
        cursor->index = index;
        cursor->low = cursor->times[index];
        cursor->high = cursor->times[index + 1];
        cursor->valueA = *(qword *)((char *)cursor + 0x40 + index * 16);
        cursor->valueB = *(qword *)((char *)cursor + 0x140 + index * 16);
    }
    return cursor->index;
}
