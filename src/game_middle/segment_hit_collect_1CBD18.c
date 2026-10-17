// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct SegmentOwner { unsigned char prefix[0xA4]; int version; };
struct SegmentIndex { unsigned short first, second; unsigned int reserved[3]; };
struct SegmentSet {
    int word0;
    qword *points;
    int word8, wordC;
    int count;
    struct SegmentIndex *segments;
};
struct SegmentObject {
    struct SegmentOwner *owner;
    unsigned char prefix[0xA0 - 4];
    struct SegmentSet set;
    unsigned char gap[0xC0 - 0xA0 - sizeof(struct SegmentSet)];
    int version;
};
struct SegmentHit {
    unsigned char prefix[0x54];
    struct SegmentIndex *segment;
    unsigned char rest[0x60 - 0x58];
};
void func_0018B1E0(struct SegmentObject *object);
int func_00119BE8(void *context, int limit, qword origin, qword direction,
                  int capacity, struct SegmentHit *output);

int func_001CBD18(void *unused0, void *unused1, struct SegmentObject *object,
                  void *context, int capacity, struct SegmentHit *hits)
{
    struct SegmentSet *set;
    qword *points;
    struct SegmentIndex *segments;
    int written, total, i;
    if (object->version != object->owner->version)
        func_0018B1E0(object);
    written = 0;
    total = 0;
    set = &object->set;
    i = set->count;
    segments = set->segments;
    points = set->points;
    while (--i >= 0) {
        struct SegmentIndex *segment = &segments[i];
        total += func_00119BE8(context, 0x7FFFFFFF,
                               points[segment->first], points[segment->second],
                               capacity - total, &hits[total]);
        while (written < total)
            hits[written++].segment = segment;
    }
    return total;
}
