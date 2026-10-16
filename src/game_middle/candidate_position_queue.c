// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int CandidateVector __attribute__((mode(TI)));
struct CandidateRecord {
    CandidateVector position;
    float angle;
    int opaque14[3];
};
struct CandidateCollection {
    CandidateVector origin;
    float heading;
    unsigned int count;
    int opaque18[2];
    struct CandidateRecord records[64];
    CandidateVector position;
};
struct Range { float low, high; };
struct Range D_003222F0 = {200.0f, 1200.0f};
struct Range D_003222F8 = {-0.785398185253143310546875f,
                          0.785398185253143310546875f};

void func_00120BA8(CandidateVector vector, float *heading,
                  float *elevation, float *distance);
int func_0011EE30(const struct Range *range, float value);
float func_0011E3B8(float angle);

int func_001A6CE0(struct CandidateCollection *collection)
{
    float heading, elevation, distance;
    CandidateVector difference;
    struct CandidateRecord *record;
    float angle;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(difference)
            : "j"(collection->position), "j"(collection->origin));
    func_00120BA8(difference, &heading, &elevation, &distance);
    if (!func_0011EE30(&D_003222F0, distance)) return 0;
    if (!func_0011EE30(&D_003222F8, elevation)) return 0;
    if (collection->count >= 64) return 0;
    record = &collection->records[collection->count++];
    record->position = collection->position;
    angle = func_0011E3B8(heading - collection->heading);
    record->angle = angle;
    if (angle < 0.0f) record->angle = 6.28318530718f - angle;
    return 1;
}

int func_001A6DD0(const void *left, const void *right)
{
    return ((const struct CandidateRecord *)left)->angle <
           ((const struct CandidateRecord *)right)->angle;
}
