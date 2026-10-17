// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct TrackEntry { short delta; short pad; unsigned char *(*method)(void *); };
struct Tracker { float limit; unsigned char gap4[0x10]; struct TrackEntry *table; };
struct Subject { unsigned char prefix[0xC]; struct TrackEntry *table; unsigned char gap10[0x2C - 0x10]; unsigned char mask; };
extern int D_00479390;
void *func_0015B820(void *self, void *bounds, int *mask);
float func_0015B068(Qword position, void *found, void *bounds);
void func_0015B5E0(void *self, struct Tracker *tracker);
void func_0015B580(void *self, struct Tracker *tracker);
void func_0015BBB8(char *self, struct Tracker *tracker)
{
    if(!D_00479390) {
        struct Subject *subject = (struct Subject *)tracker->table[1].method((char *)tracker + tracker->table[1].delta);
        unsigned char bounds[0x20];
        int mask;
        void *found = func_0015B820(self, bounds, &mask);
        int near;
        if(mask & subject->mask) {
            near = func_0015B068(*(Qword *)(subject->table[36].method((char *)subject + subject->table[36].delta) + 0x30), found, bounds) < tracker->limit;
        } else {
            near = 0;
        }
        if(near) func_0015B5E0(self, tracker);
        else func_0015B580(self, tracker);
    }
}
