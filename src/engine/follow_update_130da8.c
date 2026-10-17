// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct FollowEntry { short delta; short pad; unsigned char *(*method)(void *); };
struct FollowTarget {
    unsigned char prefix[0xC]; struct FollowEntry *table;
    unsigned char gap10[0xD4 - 0x10]; struct FollowTarget *anchor;
    unsigned char gapD8[0x114 - 0xD8]; float span; int count;
};
struct FollowSelf { void *owner; unsigned char gap4[0x20 - 4]; struct FollowTarget *target; };
extern float func_002A3160(float value);
void func_00166E48(void *owner, Qword from, Qword to, float first, float second);
void func_00166DE8(void *owner, void *matrix);
void func_00167960(void *owner, float value);
static inline float Clamp(float value, float low, float high)
{
    if(value < low) return low;
    if(value > high) return high;
    return value;
}
void func_00130DA8(struct FollowSelf *self)
{
    struct FollowTarget *target = self->target;
    if(target->anchor) {
        Qword from = *(Qword *)(target->table[36].method((unsigned char *)target + target->table[36].delta) + 0x30);
        struct FollowTarget *anchor = self->target->anchor;
        Qword to = *(Qword *)(anchor->table[36].method((unsigned char *)anchor + anchor->table[36].delta) + 0x30);
        func_00166E48(self->owner, from, to, 0.0f, 0.0f);
    } else {
        func_00166DE8(self->owner, target->table[36].method((unsigned char *)target + target->table[36].delta));
    }
    target = self->target;
    if(target->count > 0) {
        float value = func_002A3160(17.995901f / target->span) * 2.0f;
        func_00167960(self->owner, Clamp(value, 0.01f, 3.0f));
    }
}
