// Start a shot: store its state, target and offsets, stamp the start and expiry time and, when it has an owner, run the owner activation hook and refresh the shot.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VEntry { short delta; short pad; void (*method)(void *); };
struct Owner { char pad0[0xC]; VEntry *table; };
struct Shot {
    char pad00[0x30];
    Owner *owner;
    float started;
    float expires;
    void *state;
    void *target;
    char pad44[0xC];
    qword position;
    qword offset;
};
struct Clock { float now, step; };
extern Clock D_0036BB98;
extern float D_00349454;
extern "C" qword func_00222890(Shot *shot, qword position);
extern "C" void func_00262450(void *object, int id);
extern "C" void func_00222AD8(Shot *shot);

extern "C" void func_00222C50(Shot *shot, void *state, qword position, void *target, qword offset)
{
    shot->state = state;
    shot->target = target;
    shot->position = offset;
    shot->offset = func_00222890(shot, position);
    float now = D_0036BB98.now;
    shot->started = now;
    shot->expires = now + D_00349454;
    if (shot->owner) {
        shot->owner->table[56].method((char *)shot->owner + shot->owner->table[56].delta);
        func_00262450(shot->owner, 0x776);
        func_00222AD8(shot);
    }
}
