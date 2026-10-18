// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Clock { float now; float step; };
struct SeekTrack { char prefix[0x30]; qword start; char gap40[0x68]; float endTime; char gapAC[4]; qword end; };
struct SeekState { char prefix[8]; struct SeekTrack *track; char gapC[0x14]; qword current; qword target; };
extern struct Clock D_0036BB98;
void func_00118558(float tMax, float t, float s, qword a, qword b, qword c, qword d, qword *position, qword *velocity, int n);
void func_00130538(struct SeekState *self, qword *position, qword *velocity, float t)
{
    float now = D_0036BB98.now;
    struct SeekTrack *track = self->track;
    if(track->endTime <= now + t) {
        if(position) *position = self->current;
        if(velocity) *velocity = self->target;
    } else {
        func_00118558(track->endTime - now, t, 1.0f, track->start, track->end, self->current, self->target, position, velocity, 0);
    }
}
