// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct QueryPair { float a, b; };
struct QueryTriple { float a, b, c; };
struct QueryRecord {
    unsigned char prefix0[0x40];
    float x40, x44;
    unsigned char gap48[0x70 - 0x48];
    qword frame;
};
struct QuerySelf { unsigned char prefix0[0x50]; struct QueryRecord *record; };
struct QueryOut {
    qword first, second;
    unsigned char gap20[0x38 - 0x20];
    struct QueryPair nearRange;
    struct QueryPair farRange;
    struct QueryTriple limits;
    unsigned char gap54[4];
    float heading;
    float time;
    int zero60;
    float high, low;
    unsigned char gap6C[4];
    int one70;
    void *pointer74;
};
struct QueryClock { float time; };
extern struct QueryClock D_0036BB98;
extern qword D_00317560;
void *func_00292034(void *destination, int value, unsigned int bytes);
qword func_0028BCD0(void *record, void *unused, qword frame);
float func_002A3EE8(float y, float x);
static const struct QueryPair kNear = {-275.0f, 150.0f};
static const struct QueryPair kFar = {-300.0f, 200.0f};
static const struct QueryTriple kLimits = {4000.0f, 0.0f, 4.0f};
void func_001F3D48(struct QuerySelf *self, struct QueryOut *out)
{
    struct QueryRecord *record;
    qword frame;
    func_00292034(out, 0, 0x80);
    record = self->record;
    frame = record->frame;
    out->first = frame;
    out->second = func_0028BCD0(record, 0, frame);
    out->nearRange = kNear;
    out->farRange = kFar;
    out->limits = kLimits;
    out->heading = func_002A3EE8(-record->x44, -record->x40);
    out->time = D_0036BB98.time;
    out->zero60 = 0;
    out->high = 5.0f;
    out->low = -3.5f;
    out->one70 = 1;
    out->pointer74 = &D_00317560;
}
